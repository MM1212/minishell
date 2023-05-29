/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:00:04 by martiper          #+#    #+#             */
/*   Updated: 2023/05/29 15:50:41 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include <shared.h>
# include <parser/parsing.h>

# define RUNNER_HEREDOC_ERROR_MSG "here-document at \
line %d delimited by end-of-file (wanted '%s')"

typedef struct s_runner_cmd_std
{
	int	in;
	int	out;
	int	err;
}	t_runner_cmd_std;

typedef struct s_runner_cmd_deps
{
	t_parser_simple_cmds	*init_cmds;
	char					**envp;
}	t_runner_cmd_deps;

typedef struct s_runner_cmd
{
	pid_t				pid;
	char				*cmd;
	char				*path;
	char				**args;
	size_t				args_count;
	int					status;
	t_runner_cmd_std	std;
	t_runner_cmd_std	f_std;
	t_parser_lexer		*redirections;
	int					stream[2];
	int					*heredoc;
	t_runner_cmd_deps	deps;
}	t_runner_cmd;

typedef struct s_runner
{
	bool			running;
	t_runner_cmd	**cmds;
	t_runner_cmd	*c_cmd;
	void			(*run)(const char *str);
	void			(*cleanup)(void);
}	t_runner;

t_runner	*get_runner(void);
size_t		runner_sanitize_args(char **args);
void		runner_cleanup(void);
size_t		runner_count_cmds(t_parser_simple_cmds *cmds);
void		runner_init_cmds(\
	t_parser_simple_cmds *init_cmds, \
	t_runner_cmd **cmds, \
	size_t size \
);
bool		runner_get_line(\
	char *delimiter, int *fd, int line_count, bool *error);
bool		runner_handle_heredoc(t_runner_cmd *cmd, t_parser_lexer *redir);
bool		runner_handle_redir_out(t_runner_cmd *cmd, t_parser_lexer *redir);
bool		runner_handle_redir_in(t_runner_cmd *cmd, t_parser_lexer *redir);
bool		runner_handle_redirections(t_runner_cmd *cmd);
void		runner_close_redirections(t_runner_cmd *cmd);

bool		dup2_safe(int fd1, int fd2, int *store);

// RUNTIME
void		runner_handle_exit_codes(t_runner_cmd **cmds);
void		runner_handle_std(\
	t_runner_cmd *cmd \
);
void		runner_child_exit(\
	t_parser_simple_cmds *init_cmds, \
	char **envp, \
	int exit_code \
);
void		runner_handle_child(\
	t_parser_simple_cmds *init_cmds, \
	char **envp, \
	t_runner_cmd *cmd \
);
void		runner_handle_pre_std(\
	t_runner_cmd *cmd, \
	t_runner_cmd *cmds[], \
	size_t idx, \
	size_t count \
);
void		runner_per_cmd(\
	t_runner *runner, \
	size_t	vars[2], \
	t_parser_simple_cmds *init_cmds, \
	char **envp \
);

#endif
