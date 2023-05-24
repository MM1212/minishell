#include "../../include/parser/parsing.h"

t_lexer *handle_redirections(t_lexer *saver, t_simple_cmds *node, t_simple_cmds *start)
{
    t_redirect_builder b;

    b.returner = saver;
    if (saver->token > 1 && saver->token <= 5)
    {
        b.redirec = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
        b.redirec->str = ft_strdup(saver->next->str);
        if (!b.redirec->str || !b.redirec)
            (parser_error_printer(saver, 0, 0, start));
        b.redirec->token = saver->token;
        b.redirec->next = NULL;
        b.redirec->prev = NULL;
        if (!node->redirections)
            node->redirections = b.redirec;
        else
            ft_lexeradd_back(&node->redirections, b.redirec);
        b.i1 = saver->i;
        b.i2 = saver->next->i;
        b.returner = saver->next->next;
        ft_lexerdelone(&saver, b.i1);
        ft_lexerdelone(&saver, b.i2);
        node->num_redirections++;
    }
    return (b.returner);
}

int	allocate_and_fill(t_cmds_builder *b, t_lexer **guide, t_lexer *saver)
{
	b->node->str = (char **)ft_calloc(b->amount + 1, sizeof(char *));
	if (!b->node->str)
		return (parser_error_printer(saver, 0, 0, b->start)); // HERE
	b->amount = 0;
	b->node->redirections = NULL;
	while (b->saver && b->saver->token != PIPE)
	{
		b->saver = handle_redirections(b->saver, b->node, b->start);
		if (!b->saver)
			break;
		if (b->saver->token == 0)
		{
			b->node->str[b->amount++] = ft_strdup(b->saver->str);
			b->saver = b->saver->next;
		}
	}
	b->node->str[b->amount] = NULL;
	b->node->next = NULL;
	if (!b->start)
		b->start = b->node;
	else
		cmds_lstlast(b->start)->next = b->node;
	if (*guide && (*guide)->token == PIPE)
		*guide = (*guide)->next;
    return (0);
}

t_simple_cmds *build_commands(t_lexer *guide)
{
    t_lexer *saver;
    t_cmds_builder b;

    saver = guide;
    b.start = NULL;
    b.amount = 0;
    while (guide)
    {
        b.saver = guide;
        b.node = ft_calloc(1, sizeof(t_simple_cmds));
        if (!b.node)
            (parser_error_printer(saver, 0, 0, b.start)); // ERROR
        while (guide && guide->token != PIPE)
        {
            guide = guide->next;
            b.amount++;
        }
        if (allocate_and_fill(&b, &guide, saver))
            return (NULL); // ERROR
	}
	return (b.start);
}

t_simple_cmds	*parser(char *str)
{
	t_lexer			*start;
	t_simple_cmds	*cmds;

    if (!str || !str[0])
    {
        printf("no command provided.\n");
        free(str);
        return (NULL);
    }
	start = parse_build_lexer(str);
	if (!start)
    {
        free(str);
        return (NULL); // ERROR
    }
	if (check_errors(start, start, str))
    {
        free(str);
        return (NULL); // ERROR
    }
	cmds = build_commands(start);
    free(str);
	return cmds;
}

// #ifdef PARSER_TEST
int	main(int argc, char **argv)
{
	char	        *str;
    t_simple_cmds	*cmds;

	str = ft_strdup("");
	cmds = parser(str);
    if (!cmds)
        return(0);
    while (cmds)
	{
		printf("argument: %s\n", cmds->str[0]);
		printf("option: %s\n", cmds->str[1]);
        // if (ft_strncmp(cmds->str[0], "echo", 4) == 0)
        //     printf("option2: %s\n", cmds->str[2]);
		if (cmds->redirections)
		{
            printf("redirections: %s\n", cmds->redirections->str);
            printf("token: %u\n", cmds->redirections->token);
            // printf("redirections2: %s\n", cmds->redirections->next->str);
            // printf("token2: %u\n", cmds->redirections->next->token);
		}
		printf("\n");
		cmds = cmds->next;
	}
	printf("%s, len: %zu\n", str, ft_strlen(str));
    // str = ft_strdup("ls -l | \"junk here and all AHCS\" | wc -l | cat >> \" \"");
    // while (node)
    // {
    //     printf("str: %s\n", node->str);
    //     printf("token: %d\n", node->token);
    //     printf("\n");
    //     node = node->next;
    // }
	return (0);
}
// #endif
