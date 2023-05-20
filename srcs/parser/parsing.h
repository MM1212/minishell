#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include "../libft/libft.h"

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

typedef struct s_lexer_builder
{
    int     i;
    int     j;
    char    *str;
    t_lexer *start;
    t_lexer *node;
}               t_lexer_builder;

typedef struct s_simple_cmds
{
	char                    **str;
	// int                   (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

#endif