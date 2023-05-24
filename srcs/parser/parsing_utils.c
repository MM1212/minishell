/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:26 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/24 12:42:47 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

t_parser_lexer	*parser_lexer_lstlast(t_parser_lexer *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_parser_simple_cmds	*parser_cmds_lstlast(t_parser_simple_cmds *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	parser_ft_lexerdel_first(t_parser_lexer **lst)
{
	t_parser_lexer	*node;

	node = *lst;
	*lst = node->next;
	parser_ft_lexerclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

void	parser_ft_lexeradd_back(t_parser_lexer **lst, t_parser_lexer *new)
{
	t_parser_lexer	*tmp;

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

void	parser_ft_lexerdelone(t_parser_lexer **lst, int key)
{
	t_parser_lexer	*node;
	t_parser_lexer	*prev;
	t_parser_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		parser_ft_lexerdel_first(lst);
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
	parser_ft_lexerclear_one(&node);
	*lst = start;
}
