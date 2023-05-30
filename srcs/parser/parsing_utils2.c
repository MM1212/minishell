/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:31 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/29 12:13:20 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

t_parser_simple_cmds	*parser_ft_simple_cmds_clear_one(\
	t_parser_simple_cmds **lst)
{
	int	i;

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
	parser_clear_lexer((*lst)->redirections);
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	parser_lexer_constructor(t_parser_lexer_builder *b, char *str)
{
	b->index = 0;
	b->i = -1;
	b->str = str;
	b->start = NULL;
	b->node = NULL;
}

void	parser_clear_lexer(t_parser_lexer *start)
{
	t_parser_lexer	*cleanup;

	while (start)
	{
		cleanup = start;
		start = start->next;
		parser_ft_lexerclear_one(&cleanup);
	}
}

void	parser_clear_cmds(t_parser_simple_cmds *cmds)
{
	t_parser_simple_cmds	*cleanup;

	while (cmds)
	{
		cleanup = cmds;
		cmds = cmds->next;
		parser_ft_simple_cmds_clear_one(&cleanup);
	}
}

t_parser_lexer	*parser_ft_lexerclear_one(t_parser_lexer **lst)
{
	if (!lst || !(*lst))
		return (NULL);
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}
