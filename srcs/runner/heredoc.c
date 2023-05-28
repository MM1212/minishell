/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:05:03 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 16:08:56 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <env/registry_fns.h>

static void	handle_signals(int sig)
{
	t_runner_cmd *cmd;

	(void)sig;
	cmd = get_runner()->c_cmd;
	close(cmd->heredoc[0]);
	close(cmd->heredoc[1]);
	close(STDIN_FILENO);
}

bool	runner_handle_heredoc(t_runner_cmd *cmd, t_parser_lexer *redir)
{
	int		fd[2];

	env_registry_remove_quotes(&redir->str);
	if (pipe(fd) == -1)
		return (false);
	cmd->heredoc = fd;
	if (cmd->std.in != STDIN_FILENO)
		close(cmd->std.in);
	dup2(STDIN_FILENO, STDIN_FILENO);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		if (runner_get_line(redir->str, fd[1]))
			break ;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (true);
}
