/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:00:04 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 13:39:16 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include <shared.h>
# include <parser/parsing.h>

typedef struct s_runner_cmd_std
{
	int	in;
	int	out;
	int	err;
}	t_runner_cmd_std;


typedef struct s_runner_cmd
{
	pid_t				pid;
	char				*cmd;
	char				*path;
	char				**args;
	size_t				args_count;
	int					status;
	t_runner_cmd_std	std;
	t_parser_lexer		*redirections;
	int					stream[2];
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

#endif
