#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include "../libft/libft.h"

struct	s_simple_cmds;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_redirect_builder
{
	int		i1;
	int		i2;
	t_lexer	*redirec;
	t_lexer	*returner;
}				t_redirect_builder;

typedef struct s_lexer_builder
{
	int		index;
	int		i;
	int		j;
	char	*str;
	t_lexer	*start;
	t_lexer	*node;
}				t_lexer_builder;

typedef struct s_cmds_builder
{
	int						amount;
	t_lexer					*saver;
	struct s_simple_cmds	*start;
	struct s_simple_cmds	*node;
}				t_cmds_builder;

typedef struct s_simple_cmds
{
	char					**str;
	// int                   (*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

t_lexer			*build_lexer(char *str);
t_lexer			*lexer_lstlast(t_lexer *lst);
void			ft_lexerdel_first(t_lexer **lst);
void			handle_quotes(t_lexer_builder *b);
t_lexer			*ft_lexerclear_one(t_lexer **lst);
t_lexer			*ft_lexerclear_one(t_lexer **lst);
t_simple_cmds	*cmds_lstlast(t_simple_cmds *lst);
void			ft_lexerdelone(t_lexer **lst, int key);
void			handle_double_quotes(t_lexer_builder *b);
void			handle_tokens(t_lexer_builder *b, char *str);
void			ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void			lexer_constructor(t_lexer_builder *b, char *str);
int				check_errors(t_lexer *start, t_lexer *guide, char *str);
void			create_lexer_node(t_lexer_builder *b, char *str, int token);
t_lexer			*handle_redirections(t_lexer *saver, t_simple_cmds *node, \
				t_simple_cmds *start);
int				parser_error_printer(t_lexer *start, t_lexer *guide, char *str, \
				t_simple_cmds *cmds);

#endif