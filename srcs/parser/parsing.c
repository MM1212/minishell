#include "parsing.h"

t_lexer	*lexer_lstlast(t_lexer *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_simple_cmds	*cmds_lstlast(t_simple_cmds *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void    create_lexer_node(t_lexer_builder* b, char *str, int token)
{
    if (token == 0)
    {
        b->j = b->i;
        while (b->str[b->j] && b->str[b->j] != ' ')
            b->j++;
        b->node->str = ft_substr(b->str, b->i, b->j - b->i);
    }
    else
        b->node->str = ft_strdup(str);
    b->node->token = token;
    b->node->next = NULL;
    if (!b->start)
        b->start = b->node;
    else
    {
        lexer_lstlast(b->start)->next = b->node;
        b->node->prev = lexer_lstlast(b->start);
    }
    if (token == PIPE)
        b->str[b->i] = 2;
    else if (token == LESS_LESS || token == GREAT_GREAT)
        b->i++;
    else if (token == 0)
        b->i += b->j - b->i - 1;
}

void    handle_quotes(t_lexer_builder *b)
{
    b->str[b->i] = 3;
    b->j = b->i;
    while (b->str[b->j] && b->str[b->j] != '\"')
        b->j++;
    b->str[b->j] = 3;
    if (!b->str[b->j])
        printf("error\n"); // PROGRAM EXITS WITH NO MATCHING QUOTE
    b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
    b->node->token = 0;
    b->node->next = NULL;
    b->i += b->j - b->i; 
    if (!b->start)
        b->start = b->node;
    else
    {
        lexer_lstlast(b->start)->next = b->node;
        b->node->prev = lexer_lstlast(b->start);
    }   
}

void    lexer_constructor(t_lexer_builder *b, char *str)
{
    b->i = -1;
    b->str = str;
    b->start = NULL;
}

t_lexer *build_lexer(char *str)
{
    t_lexer_builder b;

    lexer_constructor(&b, str);
    while (str[++b.i])
    {
        if (str[b.i] == ' ' || str[b.i] == 3)
            str[b.i++] = 3;
        b.node = (t_lexer *)malloc(sizeof(t_lexer));
        if (!b.node)
            return (0);
        if (str[b.i] == '\"')
            handle_quotes(&b);
        else if (str[b.i] == '|')
            create_lexer_node(&b, "|", PIPE);
        else if (str[b.i] == '<' && str[b.i + 1] == '<' && str[b.i + 2] == ' ')
            create_lexer_node(&b, "<<", LESS_LESS);
        else if (str[b.i] == '>' && str[b.i + 1] == '>' && (str[b.i + 2] == ' ' || !str[b.i + 2]))
            create_lexer_node(&b, ">>", GREAT_GREAT);
        else if (str[b.i] == '<' && str[b.i + 1] == ' ')
            create_lexer_node(&b, "<", LESS);
        else if (str[b.i] == '>' && str[b.i + 1] == ' ')
            create_lexer_node(&b, ">", GREAT);
        else
            create_lexer_node(&b, 0, 0);
    }
    return (b.start);
}

t_simple_cmds   *build_commands(t_lexer *guide)
{
    int             amount;
    t_lexer         *saver;
    t_simple_cmds   *start;
    t_simple_cmds   *node;

    start = NULL;
    amount = 0;
    while (guide)
    {
        saver = guide;
        node = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
        if (!node)
            return (0);
        while (guide && guide->token != PIPE)
        {
            guide = guide->next;
            amount++;
        }
        node->str = (char **)malloc(sizeof(char *) * (amount + 1));
        if (!node->str)
            return (0);
        amount = 0;
        while (saver && saver->token != PIPE)
        {
            node->str[amount++] = ft_strdup(saver->str);
            saver = saver->next;
        }
        node->str[amount] = NULL;
        node->next = NULL;
        if (!start)
            start = node;
        else
            cmds_lstlast(start)->next = node;
        if (guide && guide->token == PIPE)
            guide = guide->next;
    }
    return (start);
}

int main()
{
    t_simple_cmds   *cmds;
    t_lexer         *start;
    t_lexer         *node;
    char             *str;

    str = ft_strdup("ls -l | \"junk here and all AHCS\" | wc -l | > cat");
    start = build_lexer(str);
    node = start;
    while (node)
    {
        printf("str: %s\n", node->str);
        printf("token: %d\n", node->token);
        printf("\n");
        node = node->next;
    }
    node = start;
    cmds = build_commands(node);
    while (cmds)
    {
        printf("argument: %s\n", cmds->str[0]);
        printf("option: %s\n", cmds->str[1]);
        printf("\n");
        cmds = cmds->next;
    }
    printf("%s, len: %d\n", str, ft_strlen(str));
    return (0);
}
