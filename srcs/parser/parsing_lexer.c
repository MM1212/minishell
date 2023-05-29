/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:09 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/29 14:22:08 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

int	parser_create_pieces(t_parser_lexer_builder *b)
{
	b->node = (t_parser_lexer *)ft_calloc(1, sizeof(t_parser_lexer));
	if (!b->node)
	{
		(parser_error_printer(b->start, 0, 0, 0));
		free(b->str);
		return (1);
	}
	parser_handle_tokens(b, b->str);
	if (!b->start->next && b->start->token == 1)
	{
		(parser_error_printer(b->start, b->start, "|", 0));
		free(b->str);
		return (1);
	}
	return (0);
}

t_parser_lexer	*parser_build_lexer(char *str)
{
	t_parser_lexer_builder	b;

	str = ft_strdup(str);
	parser_lexer_constructor(&b, str);
	while (b.str[++b.i])
	{
		while (b.str[b.i] == ' ')
			b.str[b.i++] = 3;
		if (!b.str[b.i])
			break ;
		if (parser_create_pieces(&b))
			return (NULL);
		if (!b.str[b.i])
			break ;
	}
	free(b.str);
	return (b.start);
}

void	parser_create_for_string(t_parser_lexer_builder *b)
{
	int	quote_counter;

	b->j = b->i;
	quote_counter = 0;
	while (b->str[b->j] && b->str[b->j] != ' ')
	{
		if (b->str[b->j] == '\'' || b->str[b->j] == '\"')
		{
			quote_counter++;
			if (quote_counter % 2 == 0)
				b->str[b->j] = '\x04';
		}
		b->j++;
	}
	if (b->str[b->j - 1] == '\'' || b->str[b->j - 1] == '\"')
	{
		b->j--;
		b->node->str = ft_substr(b->str, b->i, b->j++ - b->i);
	}
	else
		b->node->str = ft_substr(b->str, b->i, b->j - b->i);
}

void	parser_create_lexer_node(t_parser_lexer_builder *b, \
	char *str, int token)
{
	if (token == 0)
		parser_create_for_string(b);
	else
		b->node->str = ft_strdup(str);
	b->node->token = token;
	b->node->next = NULL;
	parser_ft_lexeradd_back(&b->start, b->node);
	if (token == PIPE)
		b->str[b->i] = 2;
	else if (token == LESS_LESS || token == GREAT_GREAT)
		b->i++;
	else if (token == 0)
		b->i += b->j - b->i - 1;
}

void	parser_handle_tokens(t_parser_lexer_builder *b, char *str)
{
	if (str[b->i] == '\'' || str[b->i] == '"')
		parser_handle_quotes(b);
	else if (str[b->i] == '|')
		parser_create_lexer_node(b, "|", PIPE);
	else if (str[b->i] == '<' && str[b->i + 1] == '<' && str[b->i + 2] == ' ')
		parser_create_lexer_node(b, "<<", LESS_LESS);
	else if (str[b->i] == '>' && str[b->i + 1] == '>' && (str[b->i + 2] == ' ' \
		|| !str[b->i + 2]))
		parser_create_lexer_node(b, ">>", GREAT_GREAT);
	else if (str[b->i] == '<' && str[b->i + 1] == ' ')
		parser_create_lexer_node(b, "<", LESS);
	else if (str[b->i] == '>' && str[b->i + 1] == ' ')
		parser_create_lexer_node(b, ">", GREAT);
	else
		parser_create_lexer_node(b, 0, 0);
}
