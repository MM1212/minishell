/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:09 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/30 10:11:07 by diogpere         ###   ########.fr       */
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
	b->j = b->i;
	while (b->str[b->j] && b->str[b->j] != ' ' && b->str[b->j] != '|' \
		&& b->str[b->j] != '<' && b->str[b->j] != '>')
		b->j++;
	b->node->str = ft_substr(b->str, b->i, b->j - b->i);
}

void	parser_create_lexer_node(t_parser_lexer_builder *b, \
	char *str, int token)
{
	if (token == 0)
	{
		parser_create_for_string(b);
		b->i += b->j - b->i - 1;
	}
	else
	{
		b->node->str = ft_strdup(str);
		if (token == PIPE)
			b->str[b->i] = 2;
		else if (token == LESS_LESS || token == GREAT_GREAT)
			b->i++;
	}
	b->node->token = token;
	b->node->next = NULL;
	parser_ft_lexeradd_back(&b->start, b->node);
}

void	parser_handle_tokens(t_parser_lexer_builder *b, char *str)
{
	if (str[b->i] == '\'' || str[b->i] == '\"')
		parser_handle_quotes(b);
	else if (str[b->i] == '|')
		parser_create_lexer_node(b, "|", PIPE);
	else if (str[b->i] == '<' && str[b->i + 1] == '<')
		parser_create_lexer_node(b, "<<", LESS_LESS);
	else if (str[b->i] == '>' && str[b->i + 1] == '>')
		parser_create_lexer_node(b, ">>", GREAT_GREAT);
	else if (str[b->i] == '<')
		parser_create_lexer_node(b, "<", LESS);
	else if (str[b->i] == '>')
		parser_create_lexer_node(b, ">", GREAT);
	else
		parser_create_lexer_node(b, 0, 0);
}
