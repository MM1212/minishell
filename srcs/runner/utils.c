/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:05:18 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 15:15:18 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd/storage.h>
#include <env/registry.h>
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
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		cmds[idx] = ft_calloc(1, sizeof(t_runner_cmd));
		if (!cmds[idx])
			return ;
		cmds[idx]->cmd = init_cmds->str[0];
		cmds[idx]->args = init_cmds->str;
		cmds[idx]->std = (t_runner_cmd_std){\
			STDIN_FILENO, \
			STDOUT_FILENO, \
			STDERR_FILENO \
		};
		cmds[idx]->status = -1;
		cmds[idx]->redirections = init_cmds->redirections;
		cmds[idx]->args_count = runner_sanitize_args(cmds[idx]->args);
		if (!get_cmds()->exists(init_cmds->str[0]))
			cmds[idx]->path = get_envp()->path->find_path(init_cmds->str[0]);
		init_cmds = init_cmds->next;
		idx++;
	}
}

bool	runner_get_line(char *delimiter, int fd)
{
	char	*line;

	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (true);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (true);
	}
	ft_putendl_fd(line, fd);
	free(line);
	return (false);
}

bool	dup2_safe(int fd1, int fd2)
{
	if (fd1 == fd2)
		return (false);
	return (dup2(fd1, fd2) != -1);
}
