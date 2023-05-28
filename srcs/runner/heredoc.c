/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:05:03 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 18:16:21 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <env/registry.h>

static void	handle_signals(int sig)
{
	t_runner_cmd	*cmd;

	if (sig != SIGINT)
		return ;
	cmd = get_runner()->c_cmd;
	close(cmd->heredoc[0]);
	close(cmd->heredoc[1]);
	close(cmd->heredoc[2]);
	runner_child_exit(cmd->deps.init_cmds, cmd->deps.envp, 130);
}

bool	runner_handle_heredoc(t_runner_cmd *cmd, t_parser_lexer *redir)
{
	int		fd[3];
	bool	error_found;
	int		line_count;

	get_envp()->expand_arg(&redir->str);
	if (pipe(fd) == -1)
		return (false);
	cmd->heredoc = fd;
	if (cmd->std.in != STDIN_FILENO)
		close(cmd->std.in);
	cmd->heredoc[2] = dup2(STDIN_FILENO, STDIN_FILENO);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	line_count = 1;
	while (fd[1] != -1)
	{
		if (runner_get_line(redir->str, fd[1], line_count, &error_found))
			break ;
		line_count++;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (error_found)
		runner_child_exit(cmd->deps.init_cmds, cmd->deps.envp, 0);
	return (true);
}
