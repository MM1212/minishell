#include "parsing.h"

t_lexer *handle_redirections(t_lexer *saver, t_simple_cmds *node, t_simple_cmds *start)
{
    t_redirect_builder b;

    b.returner = saver;
    if (saver->token > 1 && saver->token <= 5)
    {
        b.redirec = (t_lexer *)malloc(sizeof(t_lexer));
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

void	allocate_and_fill(t_cmds_builder *b)
{
	b->node->str = (char **)malloc(sizeof(char *) * (b->amount + 1));
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
	if (guide && guide->token == PIPE)
		guide = guide->next;
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
        b.node = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
        if (!b.node)
            (parser_error_printer(saver, 0, 0, b.start)); // ERROR
        while (guide && guide->token != PIPE)
        {
            guide = guide->next;
            b.amount++;
        }
        allocate_and_fill(&b);
	}
	return (b.start);
}

t_simple_cmds	*parser(char *str)
{
	t_lexer			*start;
	t_simple_cmds	*cmds;

	start = build_lexer(str);
	if (!start)
		return (NULL); // ERROR
	if (check_errors(start, start, str))
		return (NULL); // ERROR
	cmds = build_commands(start);
	if (!cmds)
		return (NULL); // ERROR
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
	printf("%s, len: %d\n", str, ft_strlen(str));
	return cmds;
}

int	main(int argc, char **argv)
{
	char	*str;

	str = ft_strdup("| echo | Hello, World!");
	parser(str);
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
