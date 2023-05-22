#include "parsing.h"

void	ft_lexerdelone(t_lexer **lst, int key)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_lexerdel_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_lexerclear_one(&node);
	*lst = start;
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

void    handle_double_quotes(t_lexer_builder *b)
{
    b->j = b->i + 1;
    while (b->str[b->j] && b->str[b->j] != '\"')
        b->j++;
    if (b->j - b->i > 1 && b->str[b->j] == '\"')
    {
        b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
        if (b->node->str[0])
            b->node->str = ft_strjoin("\"", b->node->str);
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
        b->node->i = b->index;
        b->index++;
    }
}

void    handle_quotes(t_lexer_builder *b)
{
    b->j = b->i + 1;
    while (b->str[b->j] && b->str[b->j] != '\'')
        b->j++;
    if (b->j - b->i > 1 && b->str[b->j] == '\'')
    {
        b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
        if (b->node->str[0])
            b->node->str = ft_strjoin("'", b->node->str);
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
        b->node->i = b->index;
        b->index++;
    }
}

void    lexer_constructor(t_lexer_builder *b, char *str)
{
    b->index = 0;
    b->i = -1;
    b->str = str;
    b->start = NULL;
}

void    handle_tokens(t_lexer_builder *b, char *str)
{
    if (str[b->i] == '\'')
            handle_quotes(b);
    else if (str[b->i] == '\"')
        handle_double_quotes(b);
    else if (str[b->i] == '|')
            create_lexer_node(b, "|", PIPE);
    else if (str[b->i] == '<' && str[b->i + 1] == '<' && str[b->i + 2] == ' ')
        create_lexer_node(b, "<<", LESS_LESS);
    else if (str[b->i] == '>' && str[b->i + 1] == '>' && (str[b->i + 2] == ' ' \
        || !str[b->i + 2]))
        create_lexer_node(b, ">>", GREAT_GREAT);
    else if (str[b->i] == '<' && str[b->i + 1] == ' ')
        create_lexer_node(b, "<", LESS);
    else if (str[b->i] == '>' && str[b->i + 1] == ' ')
        create_lexer_node(b, ">", GREAT);
    else
        create_lexer_node(b, 0, 0);
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
            return (0); // ERROR
        handle_tokens(&b, str);
        if (!str[b.i])
            break;
    }
    return (b.start);
}

t_lexer   *handle_redirections(t_lexer *saver, t_simple_cmds *node)
{
    t_redirect_builder b;

    b.returner = saver;
    if (saver->token > 1 && saver->token <= 5)
    {
        b.redirec = (t_lexer *)malloc(sizeof(t_lexer));
        b.redirec->str = ft_strdup(saver->next->str);
        if (!b.redirec->str || !b.redirec)
            return (0); // ERROR
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

t_simple_cmds   *build_commands(t_lexer *guide)
{
    t_cmds_builder b;

    b.start = NULL;
    b.amount = 0;
    if (guide->token == PIPE)
        return (0); // ERROR
    while (guide)
    {
        b.saver = guide;
        b.node = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
        if (!b.node)
            return (0); // ERROR
        while (guide && guide->token != PIPE)
        {
            guide = guide->next;
            b.amount++;
        }
        b.node->str = (char **)malloc(sizeof(char *) * (b.amount + 1));
        if (!b.node->str)
            return (0); // ERROR
        b.amount = 0;
        b.node->redirections = NULL;
        while (b.saver && b.saver->token != PIPE)
        {
            b.saver = handle_redirections(b.saver, b.node);
            if (!b.saver)
                break;
            if (b.saver->token == 0)
            {
                b.node->str[b.amount++] = ft_strdup(b.saver->str);
                b.saver = b.saver->next;
            }
        }
        b.node->str[b.amount] = NULL;
        b.node->next = NULL;
        if (!b.start)
            b.start = b.node;
        else
            cmds_lstlast(b.start)->next = b.node;
        if (guide && guide->token == PIPE)
                guide = guide->next;
    }
    return (b.start);
}

int     check_errors(t_lexer *guide, char *str)
{
    int     i;
    int     count_double;
    int     count_single;

    count_double = 0;
    count_single = 0;
    while (guide)
    {
        if (guide->token > 0 && !guide->next)
            return (1); // ERROR
        if (guide->token != 0 && guide->token == guide->next->token)
            return (1); // ERROR 
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
    if (count_double % 2 != 0 || count_single % 2 != 0)
        return (1); // ERROR
    return (0);
}

int main()
{
    t_simple_cmds   *cmds;
    t_lexer         *start;
    t_lexer         *node;
    char             *str;

    str = ft_strdup("ls | rev > file >> file2 | wc -l | echo \"file3file4\" | cat > file5 >> file6");
    // str = ft_strdup("ls -l | \"junk here and all AHCS\" | wc -l | cat >> \" \"");
    start = build_lexer(str);
    if (!start)
        return (1); // ERROR
    node = start;
    while (node)
    {
        printf("str: %s\n", node->str);
        printf("token: %d\n", node->token);
        printf("\n");
        node = node->next;
    }
    if (check_errors(start, str))
    {
        printf("check_errors\n");
        return (1); // ERROR
    } 
    node = start;
    cmds = build_commands(node);
    if (!cmds)
        return (1); // ERROR
    while (cmds)
    {
        printf("argument: %s\n", cmds->str[0]);
        printf("option: %s\n", cmds->str[1]);
        if (ft_strncmp(cmds->str[0], "echo", 4) == 0)
         printf("option2: %s\n", cmds->str[2]);
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
    return (0);
}
