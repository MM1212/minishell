/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:11:59 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/28 18:28:16 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

void	parser_handle_side_quotes(t_parser_lexer_builder *b, char c)
{
	char	other_set;
	char	set[3];

	other_set = c;
	if (c == '\'')
		other_set = '\"';
	else if (c == '\"')
		other_set = '\'';
	if (b->str[b->j] && (b->str[b->j + 1] == c || b->str[b->j + 1] == \
		other_set || b->str[b->j + 1] != 32))
	{
		if (b->str[b->j + 1] == other_set)
			c = other_set;
		if (b->str[b->j + 1] != c && b->str[b->j + 1] != other_set \
			&& b->str[b->j])
		{
			ft_sprintf(set, 3, "%c%c", c, '\x04');
			ft_strrep(&b->str, b->j, 1, set);
		}
		b->j += 2;
		while (b->str[b->j] && b->str[b->j] != c && b->str[b->j] != 32)
			b->j++;
	}
}

void	parser_handle_double_quotes(t_parser_lexer_builder *b)
{
	char	*tmp;

	b->j = b->i + 1;
	while (b->str[b->j] && b->str[b->j] != '\"')
		b->j++;
	parser_handle_side_quotes(b, '\"');
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
	while (b->str[b->j] && b->str[b->j] != '\'')
		b->j++;
	parser_handle_side_quotes(b, '\'');
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
