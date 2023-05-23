#include "parsing.h"

t_lexer	*ft_lexerclear_one(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

t_simple_cmds *ft_simple_cmds_clear_one(t_simple_cmds **lst)
{
	int i;

	i = 0;
	if ((*lst)->str)
	{
		while ((*lst)->str[i])
		{
			free((*lst)->str[i]);
			(*lst)->str[i] = NULL;
			i++;
		}
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	if ((*lst)->hd_file_name)
	{
		free((*lst)->hd_file_name);
		(*lst)->hd_file_name = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void lexer_constructor(t_lexer_builder *b, char *str)
{
    b->index = 0;
    b->i = -1;
    b->str = str;
    b->start = NULL;
    b->node = NULL;
}

int	parser_error_printer(t_lexer *start, t_lexer *guide, char *str, t_simple_cmds *cmds)
{
	t_simple_cmds *cleanup_cmds;
    t_lexer *cleanup;
    if (!str)
        printf("syntax error near unexpected token '%s'\n", guide->str);
	else if (!str && !guide)
		printf("memory allocation error\n");
    else
        printf("syntax error near unexpected token %s\n", str);
    while (start)
    {
        cleanup = start;
        start = start->next;
        ft_lexerclear_one(&cleanup);
    }
	if (cmds)
	{
		while (cmds)
		{
			cleanup_cmds = cmds;
			cmds = cmds->next;
			ft_simple_cmds_clear_one(&cleanup_cmds);
		}
	}
    return (0);
}

int check_errors(t_lexer *start, t_lexer *guide, char *str)
{
    int i;
    int count_double;
    int count_single;

    count_double = 0;
    count_single = 0;
    while (guide)
    {
        if (guide->token > 0 && !guide->next)
            return (parser_error_printer(start, guide, 0, 0)); // ERROR
        if (guide->token != 0 && guide->token == guide->next->token)
            return (parser_error_printer(start, guide, 0, 0)); // ERROR
        guide = guide->next;
    }
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\"')
            count_double++;
        else if (str[i] == '\'')
            count_single++;
    }
    if (count_double % 2 != 0)
        return (parser_error_printer(start, guide, "\"", 0)); // ERROR
    else if (count_single % 2 != 0)
        return (parser_error_printer(start, guide, "\'", 0)); // ERROR
    return (0);
}