/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:23:16 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/29 14:21:04 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <shared.h>

struct	s_parser_simple_cmds;

typedef enum s_parser_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_parser_tokens;

typedef struct s_parser_lexer
{
	char					*str;
	t_parser_tokens			token;
	int						i;
	struct s_parser_lexer	*next;
	struct s_parser_lexer	*prev;
}	t_parser_lexer;

typedef struct s_parser_redirect_builder
{
	int				i1;
	int				i2;
	t_parser_lexer	*redirec;
	t_parser_lexer	*returner;
}				t_parser_redirect_builder;

typedef struct s_parser_lexer_builder
{
	int				index;
	int				i;
	int				j;
	char			*str;
	t_parser_lexer	*start;
	t_parser_lexer	*node;
}				t_parser_lexer_builder;

typedef struct s_parser_cmds_builder
{
	int							amount;
	t_parser_lexer				*saver;
	struct s_parser_simple_cmds	*start;
	struct s_parser_simple_cmds	*node;
}				t_parser_cmds_builder;

typedef struct s_parser_simple_cmds
{
	char						**str;
	int							num_redirections;
	t_parser_lexer				*redirections;
	struct s_parser_simple_cmds	*next;
	struct s_parser_simple_cmds	*prev;
}	t_parser_simple_cmds;

t_parser_lexer			*parser_build_lexer(char *str);
void					parser_clear_lexer(t_parser_lexer *start);
t_parser_lexer			*parser_lexer_lstlast(t_parser_lexer *lst);
void					parser_clear_cmds(t_parser_simple_cmds *cmds);
void					parser_ft_lexerdel_first(t_parser_lexer **lst);
void					parser_handle_quotes(t_parser_lexer_builder *b);
t_parser_lexer			*parser_ft_lexerclear_one(t_parser_lexer **lst);
t_parser_lexer			*parser_ft_lexerclear_one(t_parser_lexer **lst);
t_parser_simple_cmds	*parser_cmds_lstlast(t_parser_simple_cmds *lst);
void					parser_ft_lexerdelone(t_parser_lexer **lst, int key);
void					parser_handle_quotes(t_parser_lexer_builder *b);
void					parser_handle_tokens(t_parser_lexer_builder *b, \
						char *str);
void					parser_ft_lexeradd_back(t_parser_lexer **lst, \
						t_parser_lexer *new);
void					parser_lexer_constructor(t_parser_lexer_builder *b, \
						char *str);
int						parser_check_errors(t_parser_lexer *start, \
						t_parser_lexer *guide, char *str);
void					parser_create_lexer_node(t_parser_lexer_builder *b, \
						char *str, int token);
t_parser_lexer			*parser_handle_redirections(t_parser_lexer *saver, \
						t_parser_simple_cmds *node, \
						t_parser_simple_cmds *start);
int						parser_error_printer(t_parser_lexer *start, \
						t_parser_lexer *guide, char *str, \
						t_parser_simple_cmds *cmds);
t_parser_simple_cmds	*parser_ft_simple_cmds_clear_one(t_parser_simple_cmds \
						**lst);
t_parser_simple_cmds	*parser(char *str);
void					parser_handle_quotes(t_parser_lexer_builder *b);
void					parser_handle_quotes(t_parser_lexer_builder *b);

#endif
