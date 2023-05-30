/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:49:19 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 12:11:49 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <context/context.h>
#include <utils/quit.h>
#include <env/registry.h>
#include <cmd/storage.h>
#include <env/path/path.h>
#include <utils/error.h>

void	runner_handle_child(\
	t_parser_simple_cmds *init_cmds, \
	char **envp, \
	t_runner_cmd *cmd \
)
{
	int	status;

	runner_handle_std(cmd);
	if (get_cmds()->exists(cmd->cmd))
	{
		status = get_cmds()->exec(\
		cmd->cmd, \
		(int)cmd->args_count, cmd->args);
		close(cmd->f_std.in);
		close(cmd->f_std.out);
		runner_child_exit(init_cmds, envp, status);
	}
	else
	{
		if (!cmd->path)
			runner_child_exit(init_cmds, envp, 127);
		if (execve(cmd->path, \
			cmd->args, envp) == -1)
		{
			display_error("execve", NULL);
			runner_child_exit(init_cmds, envp, 127);
		}
	}
}

void	runner_handle_pre_std(\
	t_runner_cmd *cmd, \
	t_runner_cmd *cmds[], \
	size_t idx, \
	size_t count
)
{
	if (idx == 0)
		cmd->std.in = STDIN_FILENO;
	else
		cmd->std.in = cmds[idx - 1]->stream[0];
	if (idx == count - 1)
		cmd->std.out = STDOUT_FILENO;
	else
		cmd->std.out = cmd->stream[1];
}

void	runner_per_cmd(\
	t_runner *runner, \
	size_t	vars[2], \
	t_parser_simple_cmds *init_cmds, \
	char **envp \
)
{
	size_t	count;
	size_t	idx;

	idx = vars[0];
	count = vars[1];
	if (pipe(runner->c_cmd->stream) < 0)
		quit(127);
	runner_handle_pre_std(runner->c_cmd, runner->cmds, idx, count);
	runner->c_cmd->pid = fork();
	if (runner->c_cmd->pid < 0)
		quit(127);
	else if (runner->c_cmd->pid == 0)
		runner_handle_child(init_cmds, envp, runner->c_cmd);
	if (idx > 0)
		close(runner->c_cmd->std.in);
	else if (idx == count - 1)
		close(runner->c_cmd->stream[0]);
	close(runner->c_cmd->stream[1]);
}
