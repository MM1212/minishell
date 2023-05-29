/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:11:59 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/29 13:06:34 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

void	parser_handle_double_quotes(t_parser_lexer_builder *b)
{
	char	*tmp;

	b->j = b->i + 1;
	while ((b->str[b->j] && b->str[b->j] != '\'' && b->str[b->j] == '\"') \
		|| (b->str[b->j] && b->str[b->j] != 32))
		b->j++;
	if (b->j - b->i > 1 && (b->str[b->j] == '\"' || b->str[b->j] == '\'' \
		|| b->str[b->j] == 32 || !b->str[b->j]))
	{
		b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i);
		if (b->node->str[0])
		{
			tmp = b->node->str;
			b->node->str = ft_strjoin("\"", b->node->str);
			free(tmp);
		}
		b->node->token = 0;
		b->node->next = NULL;
		b->i += b->j - b->i;
		parser_ft_lexeradd_back(&b->start, b->node);
		b->node->i = b->index;
		b->index++;
	}
}

void	parser_handle_quotes(t_parser_lexer_builder *b)
{
	char	*tmp;

	b->j = b->i + 1;
	while ((b->str[b->j] && b->str[b->j] != '\'' && b->str[b->j] == '\"') \
		|| (b->str[b->j] && b->str[b->j] != 32))
		b->j++;
	if (b->j - b->i > 1 && (b->str[b->j] == '\'' || b->str[b->j] == '\"' \
		|| b->str[b->j] == 32 || !b->str[b->j]))
	{
		b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i);
		if (b->node->str[0])
		{
			tmp = b->node->str;
			b->node->str = ft_strjoin("'", b->node->str);
			free(tmp);
		}
		b->node->token = 0;
		b->node->next = NULL;
		b->i += b->j - b->i;
		parser_ft_lexeradd_back(&b->start, b->node);
		b->node->i = b->index;
		b->index++;
	}
}
