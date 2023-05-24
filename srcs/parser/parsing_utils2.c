/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:31 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/24 13:02:07 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

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