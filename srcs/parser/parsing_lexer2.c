/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:11:59 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/29 00:06:28 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

void	parser_handle_quotes(t_parser_lexer_builder *b)
{
	char	c;
	int		pair;

	pair = 0;
	b->j = b->i;
	c = b->str[b->j];
	while (b->str[b->j])
	{
		if (ft_strchr("'\"", b->str[b->j]) != NULL && pair == 2)
		{
			c = b->str[b->j];
			pair = 1;
		}
		else if (b->str[b->j] == c)
			pair++;
		b->j++;
		if (pair == 2 && (b->str[b->j] && b->str[b->j] == ' '))
			break ;
	}
	b->node->str = ft_substr(b->str, b->i, b->j - b->i);
	b->node->token = 0;
	b->node->next = NULL;
	b->i += b->j - b->i;
	parser_ft_lexeradd_back(&b->start, b->node);
	b->node->i = b->index++;
}
