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

t_lexer *build_lexer(char *str)
{
    t_lexer *start;
    t_lexer *node;
    int i;
    int j;

    i = 0;
    start = NULL;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            str[i] = 3;
            i++;
        }
        node = (t_lexer *)malloc(sizeof(t_lexer));
        if (!node)
            return (0);
        if (str[i] == '|')
        {
            str[i] = 2;
            node->str = ft_strdup("|");
            node->token = PIPE;
            node->next = NULL;
            if (!start)
                start = node;
            else
            {
                lexer_lstlast(start)->next = node;
                node->prev = lexer_lstlast(start);
            }
        }
        else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == ' ')
        {
            node->str = ft_strdup("<<");
            node->token = LESS_LESS;
            node->next = NULL;
            i += 1;
            if (!start)
                start = node;
            else
            {
                lexer_lstlast(start)->next = node;
                node->prev = lexer_lstlast(start);
            }
        }
        else if (str[i] == '>' && str[i + 1] == '>' && (str[i + 2] == ' ' || !str[i + 2]))
        {
            node->str = ft_strdup(">>");
            node->token = GREAT_GREAT;
            node->next = NULL;
            i += 1;
            if (!start)
                start = node;
            else
            {
                lexer_lstlast(start)->next = node;
                node->prev = lexer_lstlast(start);
            }
        }
        else if (str[i] == '<' && str[i + 1] == ' ')
        {
            node->str = ft_strdup("<");
            node->token = LESS;
            node->next = NULL;
            if (!start)
                start = node;
            else
            {
                lexer_lstlast(start)->next = node;
                node->prev = lexer_lstlast(start);
            }
        }
        else if (str[i] == '>' && str[i + 1] == ' ')
        {
            node->str = ft_strdup(">");
            node->token = GREAT;
            node->next = NULL;
            if (!start)
                start = node;
            else
            {
                lexer_lstlast(start)->next = node;
                node->prev = lexer_lstlast(start);
            }
        }
        else
        {
            j = i;
            while (str[j] && str[j] != ' ')
            {
                j++;
            }   
            node->str = ft_substr(str, i, j - i);
            node->token = 0;
            node->next = NULL;
            i += j - i - 1;
            if (!start)
                start = node;
            else
            {
                lexer_lstlast(start)->next = node;
                node->prev = lexer_lstlast(start);
            }
        }
        i++;
    }
    return (start);
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
        if (guide != NULL)
        {
            if (guide && guide->token == PIPE)
                guide = guide->next;
        }
    }
    return (start);
}

int main()
{
    t_simple_cmds   *cmds;
    t_lexer         *start;
    t_lexer         *node;
    char             *str;

    str = ft_strdup("ls -l | cat -e | wc -l");
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
