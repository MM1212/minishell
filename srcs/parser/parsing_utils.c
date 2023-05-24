#include "../../include/parser/parsing.h"

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

void	ft_lexerdel_first(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	ft_lexerclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void    ft_lexerdelone(t_lexer **lst, int key)
{
    t_lexer *node;
    t_lexer *prev;
     t_lexer *start;

    start = *lst;
    node = start;
    if ((*lst)->i == key)
    {
        ft_lexerdel_first(lst);
        return;
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
