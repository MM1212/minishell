/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:05:03 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 12:16:18 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <env/registry.h>

static void	handle_exit(t_runner_cmd *cmd)
{
	runner_close_redirections(cmd);
	close(cmd->stream[0]);
	close(cmd->stream[1]);
	runner_child_exit(cmd->deps.init_cmds, cmd->deps.envp, 130);
}

static void	handle_signals(int sig)
{
	t_runner_cmd	*cmd;

	if (sig != SIGINT)
		return ;
	cmd = get_runner()->c_cmd;
	close(cmd->heredoc[0]);
	close(cmd->heredoc[1]);
	close(cmd->heredoc[2]);
	ft_printf("\n");
	cmd->heredoc[1] = -1;
}

static void	on_heredoc_exit(t_runner_cmd *cmd, bool error_found)
{
	char	*line;

	close(cmd->heredoc[2]);
	if (cmd->heredoc[1] != -1)
		close(cmd->heredoc[1]);
	if (error_found)
	{
		close(cmd->heredoc[0]);
		handle_exit(cmd);
	}
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	dup2(cmd->heredoc[0], STDIN_FILENO);
	close(cmd->heredoc[0]);
}

bool	runner_handle_heredoc(t_runner_cmd *cmd, t_parser_lexer *redir)
{
	int		fd[3];
	bool	error_found;
	int		line_count;

	if (pipe(fd) == -1)
		return (false);
	cmd->heredoc = fd;
	if (cmd->std.in != STDIN_FILENO)
		close(cmd->std.in);
	cmd->heredoc[2] = dup2(STDIN_FILENO, STDIN_FILENO);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	line_count = 1;
	while (1)
	{
		if (runner_get_line(redir->str, &fd[1], line_count++, &error_found))
			break ;
	}
	on_heredoc_exit(cmd, error_found);
	return (true);
}
