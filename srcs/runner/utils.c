/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:05:18 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 12:01:29 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd/storage.h>
#include <env/registry.h>
#include <env/registry_fns.h>
#include <utils/error.h>
#include <utils/quit.h>
#include "runner/runner.h"

void	runner_cleanup(void)
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

size_t	runner_count_cmds(t_parser_simple_cmds *cmds)
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

void	runner_init_cmds(\
	t_parser_simple_cmds *init_cmds, \
	t_runner_cmd **cmds, \
	size_t size \
)
{
	size_t					idx;
	t_parser_simple_cmds	*tmp;

	idx = 0;
	tmp = init_cmds;
	while (idx < size)
	{
		cmds[idx] = ft_calloc(1, sizeof(t_runner_cmd));
		if (!cmds[idx])
			return ;
		cmds[idx]->std = (t_runner_cmd_std){\
			STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO \
		};
		cmds[idx]->f_std = cmds[idx]->std;
		cmds[idx]->status = -1;
		cmds[idx]->redirections = init_cmds->redirections;
		cmds[idx]->args_count = runner_sanitize_args(init_cmds->str);
		cmds[idx]->cmd = init_cmds->str[0];
		cmds[idx]->args = init_cmds->str;
		if (!get_cmds()->exists(cmds[idx]->cmd))
			cmds[idx]->path = get_envp()->path->find_path(cmds[idx]->cmd);
		cmds[idx]->deps.init_cmds = tmp;
		init_cmds = init_cmds->next;
		idx++;
	}
}

bool	runner_get_line(char *delimiter, int *fd, int count, bool *error)
{
	char	*line;
	char	error_msg[256];
	char	*sanitized_delim;

	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	*error = false;
	if (!line)
	{
		*error = true;
		if (*fd != -1)
		{
			ft_sprintf(error_msg, 256, RUNNER_HEREDOC_ERROR_MSG, \
				count, delimiter);
			display_error("warning", error_msg);
		}
		return (true);
	}
	if (!ft_strchr(delimiter, '"') && !ft_strchr(delimiter, '\''))
		(get_envp())->raw_expand_arg(&line);
	sanitized_delim = ft_strdup(delimiter);
	env_registry_remove_quotes(&sanitized_delim);
	if (ft_strcmp(line, sanitized_delim) == 0)
		return (free(sanitized_delim), free(line), true);
	return (free(sanitized_delim), ft_putendl_fd(line, *fd), free(line), false);
}

bool	dup2_safe(int fd1, int fd2, int *store)
{
	int	tmp;

	if (fd1 == fd2)
		return (false);
	tmp = dup2(fd1, fd2);
	*store = tmp;
	return (tmp != -1);
}
