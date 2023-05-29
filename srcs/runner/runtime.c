/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:47:49 by martiper          #+#    #+#             */
/*   Updated: 2023/05/29 15:51:13 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <context/context.h>
#include <utils/quit.h>
#include <env/registry.h>
#include <cmd/storage.h>
#include <env/path/path.h>
#include <utils/error.h>

void	runner_handle_exit_codes(t_runner_cmd **cmds)
{
	size_t			idx;
	char			*status_code;
	t_cmd			*cmd;
	t_envp			*env;

	idx = 0;
	env = get_envp();
	while (cmds[idx])
	{
		waitpid(cmds[idx]->pid, &cmds[idx]->status, 0);
		if (WIFEXITED(cmds[idx]->status))
			cmds[idx]->status = WEXITSTATUS(cmds[idx]->status);
		if (get_cmds()->exists(cmds[idx]->cmd))
		{
			cmd = get_cmds()->get(cmds[idx]->cmd);
			if (cmd->on_execute)
				cmd->on_execute(cmds[idx]->args_count, \
					cmds[idx]->args, &cmds[idx]->status);
		}
		status_code = ft_itoa(cmds[idx]->status);
		env->set("?", status_code);
		free(status_code);
		idx++;
	}
}

void	runner_handle_std(\
	t_runner_cmd *cmd \
)
{
	if (!runner_handle_redirections(cmd))
	{
		display_error(cmd->cmd, NULL);
		runner_close_redirections(cmd);
		close(cmd->stream[0]);
		close(cmd->stream[1]);
		runner_child_exit(cmd->deps.init_cmds, cmd->deps.envp, errno);
	}
	if (dup2_safe(cmd->std.in, STDIN_FILENO, &cmd->f_std.in))
		close(cmd->std.in);
	if (dup2_safe(cmd->std.out, STDOUT_FILENO, &cmd->f_std.out))
		close(cmd->std.out);
	if (dup2_safe(cmd->std.err, STDERR_FILENO, &cmd->f_std.err))
		close(cmd->std.err);
	close(cmd->stream[0]);
	close(cmd->stream[1]);
}

void	runner_child_exit(\
	t_parser_simple_cmds *init_cmds, \
	char **envp, \
	int exit_code \
)
{
	destroy_all_contexts();
	parser_clear_cmds(init_cmds);
	ft_split_free(envp);
	exit(exit_code);
}
