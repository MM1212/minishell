/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:07:32 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 15:26:16 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <context/context.h>
#include <parser/parsing.h>
#include <utils/quit.h>
#include <env/registry.h>
#include <cmd/storage.h>
#include <env/path/path.h>


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
		close(runner->cmds[idx]->std.in);
		close(runner->cmds[idx]->std.out);
		close(runner->cmds[idx]->std.err);
		ft_split_free(runner->cmds[idx]->args);
		free(runner->cmds[idx++]);
	}
	free(runner->cmds);
	runner->cmds = NULL;
	runner->c_cmd = NULL;
	runner->running = false;
}

static size_t	runner_count_cmds(t_simple_cmds *cmds)
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
	char	*tmp;

	idx = 1;
	envp = get_envp();
	while (args[idx])
	{
		if (args[idx][0] == '"' || args[idx][0] == '\'')
		{
			arg = ft_strdup(args[idx + 1]);
			if (!arg)
				return (0);
			tmp = arg;
			if (args[idx][0] == '"')
			{
				arg = envp->expand_arg(arg);
				free(tmp);
			}
			free(args[idx]);
			args[idx++] = arg;
		}
		idx++;
	}
	return (idx);
}

static void	runner_init_cmds(\
	t_simple_cmds	*init_cmds, \
	t_runner_cmd	**cmds, \
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
		cmds[idx]->args_count = runner_sanitize_args(cmds[idx]->args);
		if (!get_cmds()->exists(init_cmds->str[0]))
			cmds[idx]->path = get_envp()->path->find_path(init_cmds->str[0]);
		init_cmds = init_cmds->next;
		idx++;
	}
}

static bool dup2_safe(int fd1, int fd2)
{
	if (fd1 == fd2)
		return (false);
	return (dup2(fd1, fd2) != -1);
}

static void runner_run(const char *str)
{
	t_runner		*runner;
	t_simple_cmds	*init_cmds;
	size_t			count;
	char			**envp;
	char			*status_code;

	runner = get_runner();
	if (!runner)
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
		ft_printf("Is %s a builtin? %d\n", cmd->cmd, get_cmds()->exists(cmd->cmd));
		cmd->pid = fork();
		// TODO: ERROR HANDLING AND CLEAN EXIT
		if (cmd->pid < 0)
			quit(127);
		else if (cmd->pid == 0)
		{
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
				execve(cmd->path, cmd->args, envp);
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
		if (get_cmds()->exists(runner->cmds[idx]->cmd))
		{
			t_cmd *cmd = get_cmds()->get(runner->cmds[idx]->cmd);
			if (cmd->on_execute)
				cmd->on_execute(runner->cmds[idx]->status);
		}
		status_code = ft_itoa(runner->cmds[idx]->status);
		get_envp()->set("?", status_code);
		free(status_code);
		idx++;
	}
	ft_simple_cmds_clear_one(&init_cmds);
	ft_split_free(envp);
	runner_cleanup();
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
