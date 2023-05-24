/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:07:32 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 16:51:18 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <context/context.h>
#include <utils/quit.h>
#include <env/registry.h>
#include <cmd/storage.h>
#include <env/path/path.h>
#include <utils/error.h>


static void runner_cleanup(void)
{
	t_runner	*runner;
	int			idx;

	runner = get_runner();
	if (!runner || !runner->running)
		return ;
	idx = 0;
	while (runner->cmds[idx])
	{
		if (runner->cmds[idx]->std.in != STDIN_FILENO)
			close(runner->cmds[idx]->std.in);
		if (runner->cmds[idx]->std.out != STDOUT_FILENO)
			close(runner->cmds[idx]->std.out);
		if (runner->cmds[idx]->std.err != STDERR_FILENO)
			close(runner->cmds[idx]->std.err);
		if (runner->cmds[idx]->path)
			free(runner->cmds[idx]->path);
		free(runner->cmds[idx++]);
	}
	free(runner->cmds);
	runner->cmds = NULL;
	runner->c_cmd = NULL;
	runner->running = false;
}

static size_t	runner_count_cmds(t_parser_simple_cmds *cmds)
{
	size_t	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static size_t runner_sanitize_args(char **args)
{
	t_envp	*envp;
	size_t	idx;
	char	*arg;

	idx = 1;
	envp = get_envp();
	while (args[idx])
	{
		if (args[idx][0] != '\'')
		{
			if (args[idx][0] == '"')
				arg = ft_strdup(args[idx] + 1);
			else
				arg = ft_strdup(args[idx]);
			if (!arg)
				return (0);
			free(args[idx]);
			args[idx] = envp->expand_arg(arg);
			free(arg);
		}
		else
		{
			arg = ft_strdup(args[idx] + 1);
			if (!arg)
				return (0);
			free(args[idx]);
			args[idx] = arg;
		}
		idx++;
	}
	return (idx);
}

static void	runner_init_cmds(\
	t_parser_simple_cmds	*init_cmds, \
	t_runner_cmd			**cmds, \
	size_t size \
)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		cmds[idx] = ft_calloc(1, sizeof(t_runner_cmd));
		if (!cmds[idx])
			return ;
		cmds[idx]->cmd = init_cmds->str[0];
		cmds[idx]->args = init_cmds->str;
		cmds[idx]->std = (t_runner_cmd_std){STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
		cmds[idx]->status = -1;
		cmds[idx]->redirections = init_cmds->redirections;
		cmds[idx]->args_count = runner_sanitize_args(cmds[idx]->args);
		if (!get_cmds()->exists(init_cmds->str[0]))
			cmds[idx]->path = get_envp()->path->find_path(init_cmds->str[0]);
		init_cmds = init_cmds->next;
		idx++;
	}
}

static bool	dup2_safe(int fd1, int fd2)
{
	if (fd1 == fd2)
		return (false);
	return (dup2(fd1, fd2) != -1);
}

static bool	runner_handle_redirections(t_runner_cmd *cmd)
{
	t_parser_lexer	*redir;
	int				fd;
	int				flags;

	if (!cmd || !cmd->redirections)
		return (true);

	redir = cmd->redirections;
	flags = 0;
	while (redir)
	{
		if (redir->token == GREAT || redir->token == GREAT_GREAT)
		{
			if (cmd->std.out != STDOUT_FILENO)
				close(cmd->std.out);
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			if (redir->token == GREAT_GREAT)
				flags = O_WRONLY | O_CREAT | O_APPEND;
			fd = open(redir->str, flags, 0644);
			if (fd == -1)
				return (false);
			cmd->std.out = fd;
		}
		else if (redir->token == LESS)
		{
			if (cmd->std.in != STDIN_FILENO)
				close(cmd->std.in);
			fd = open(redir->str, O_RDONLY);
			if (fd == -1)
				return (false);
			cmd->std.in = fd;
		}
		else if (redir->token == LESS_LESS)
		{
			char *delimiter;
			int	fd[2];

			delimiter = redir->str;
			if (pipe(fd) == -1)
				return (false);
			if (cmd->std.in != STDIN_FILENO)
				close(cmd->std.in);
			dup2(STDIN_FILENO, STDIN_FILENO);
			if (*redir->str == '"' || *redir->str == '\'')
				delimiter++;
			while (1)
			{
				ft_printf("> ");
				char *line = get_next_line(STDIN_FILENO);
				if (!line)
					break ;
				if (ft_strcmp(line, delimiter) == 0)
				{
					free(line);
					break ;
				}
				ft_putendl_fd(line, fd[1]);
				free(line);
			}
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}

		redir = redir->next;
	}
	return (true);
}

static void	runner_close_redirections(t_runner_cmd *cmd)
{
	if (!cmd || !cmd->redirections)
		return ;
	if (cmd->std.in != STDIN_FILENO)
		close(cmd->std.in);
	if (cmd->std.out != STDOUT_FILENO)
		close(cmd->std.out);
	if (cmd->std.err != STDERR_FILENO)
		close(cmd->std.err);
}

static void runner_run(const char *str)
{
	t_runner				*runner;
	t_parser_simple_cmds	*init_cmds;
	size_t			count;
	char			**envp;
	char			*status_code;
	t_envp	*env;

	env = get_envp();
	runner = get_runner();
	if (!runner || !env)
		return ;
	init_cmds = parser((char *)str);
	if (!init_cmds)
		return ;
	count = runner_count_cmds(init_cmds);
	if (!count)
		return ;
	runner->cmds = ft_calloc(count + 1, sizeof(t_runner_cmd *));
	if (!runner->cmds)
		return ;
	runner->running = true;
	runner_init_cmds(init_cmds, runner->cmds, count);
	size_t	idx = 0;
	envp = get_envp()->get_env();
	while (runner->cmds[idx])
	{
		t_runner_cmd	*cmd = runner->cmds[idx];
		if (pipe(cmd->stream) < 0)
			quit(127);
		if (idx == 0)
			cmd->std.in = STDIN_FILENO;
		else
			cmd->std.in = runner->cmds[idx - 1]->stream[0];
		if (idx == count - 1)
			cmd->std.out = STDOUT_FILENO;
		else
			cmd->std.out = cmd->stream[1];
		cmd->pid = fork();
		// TODO: ERROR HANDLING AND CLEAN EXIT
		if (cmd->pid < 0)
			quit(127);
		else if (cmd->pid == 0)
		{
			if (!runner_handle_redirections(cmd))
			{
				runner_close_redirections(cmd);
				display_error(cmd->cmd, NULL);
				exit(errno);
			}
			if (dup2_safe(cmd->std.in, STDIN_FILENO))
				close(cmd->std.in);
			if (dup2_safe(cmd->std.out, STDOUT_FILENO))
				close(cmd->std.out);
			if (dup2_safe(cmd->std.err, STDERR_FILENO))
				close(cmd->std.err);
			close(cmd->stream[0]);
			close(cmd->stream[1]);
			if (get_cmds()->exists(cmd->cmd))
				exit(get_cmds()->exec(cmd->cmd, (int)cmd->args_count, cmd->args));
			else
			{
				if (!cmd->path)
					exit(127);
				if (execve(cmd->path, cmd->args, envp) == -1)
				{
					display_error("execve", NULL);
					exit(1);
				}
			}

		}
		if (idx > 0)
			close(cmd->std.in);
		else if (idx == count - 1)
			close(cmd->stream[0]);
		close(cmd->stream[1]);
		idx++;
	}
	idx = 0;
	while (runner->cmds[idx])
	{
		waitpid(runner->cmds[idx]->pid, &runner->cmds[idx]->status, 0);
		if (WIFEXITED(runner->cmds[idx]->status))
			runner->cmds[idx]->status = WEXITSTATUS(runner->cmds[idx]->status);
		if (get_cmds()->exists(runner->cmds[idx]->cmd))
		{
			t_cmd *cmd = get_cmds()->get(runner->cmds[idx]->cmd);
			if (cmd->on_execute)
				cmd->on_execute(runner->cmds[idx]->args_count, runner->cmds[idx]->args, runner->cmds[idx]->status);
		}
		status_code = ft_itoa(runner->cmds[idx]->status);
		env->set("?", status_code);
		free(status_code);
		idx++;
	}
	runner_cleanup();
	parser_clear_cmds(init_cmds);
	ft_split_free(envp);
}

static t_runner *runner_create(void)
{
	t_runner *runner;

	runner = ft_calloc(1, sizeof(t_runner));
	if (!runner)
		return (NULL);
	runner->run = runner_run;
	runner->cleanup = runner_cleanup;
	return (runner);
}

static void	runner_destroy(t_runner *runner)
{
	if (!runner)
		return ;
	runner_cleanup();
	free(runner);
}

t_runner	*get_runner(void)
{
	return (
		get_context(\
			CONTEXT_ID_RUNNER, \
			(t_context_construct_fn)runner_create, \
			(t_context_destruct_fn)runner_destroy \
		)
	);
}
