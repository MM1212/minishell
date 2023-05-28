/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unix.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:11:06 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 15:16:18 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"

bool	runner_handle_redir_out(t_runner_cmd *cmd, t_parser_lexer *redir)
{
	int	fd;
	int	flags;

	flags = 0;
	if (cmd->std.out != STDOUT_FILENO)
		close(cmd->std.out);
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (redir->token == GREAT_GREAT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->str, flags, 0644);
	if (fd == -1)
		return (false);
	cmd->std.out = fd;
	return (true);
}

bool	runner_handle_redir_in(t_runner_cmd *cmd, t_parser_lexer *redir)
{
	int	fd;

	if (cmd->std.in != STDIN_FILENO)
		close(cmd->std.in);
	fd = open(redir->str, O_RDONLY);
	if (fd == -1)
		return (false);
	cmd->std.in = fd;
	return (true);
}

bool	runner_handle_redirections(t_runner_cmd *cmd)
{
	t_parser_lexer	*redir;

	if (!cmd || !cmd->redirections)
		return (true);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->token == GREAT || redir->token == GREAT_GREAT)
		{
			if (!runner_handle_redir_out(cmd, redir))
				return (false);
		}
		else if (redir->token == LESS)
		{
			if (!runner_handle_redir_in(cmd, redir))
				return (false);
		}
		else if (redir->token == LESS_LESS)
		{
			if (!runner_handle_heredoc(cmd, redir))
				return (false);
		}
		redir = redir->next;
	}
	return (true);
}

void	runner_close_redirections(t_runner_cmd *cmd)
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
