/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:09 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 18:03:29 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

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
		b.node = (t_parser_lexer *)ft_calloc(1, sizeof(t_parser_lexer));
		if (!b.node)
		{
			(parser_error_printer(b.start, 0, 0, 0));
			free(b.str);
			return (NULL);
		}
		parser_handle_tokens(&b, b.str);
		if (!b.start->next && b.start->token == 1)
		{
			(parser_error_printer(b.start, b.start, "|", 0));
			free(b.str);
			return (NULL);
		}
		if (!b.str[b.i])
			break ;
	}
	free(b.str);
	return (b.start);
}

void	parser_create_lexer_node(t_parser_lexer_builder *b, \
	char *str, int token)
{
	if (token == 0)
	{
		b->j = b->i;
		while (b->str[b->j] && b->str[b->j] != ' ' && \
			b->str[b->j] != '\'' && b->str[b->j] != '\"')
			b->j++;
		b->node->str = ft_substr(b->str, b->i, b->j - b->i);
	}
	else
		b->node->str = ft_strdup(str);
	b->node->token = token;
	b->node->next = NULL;
	if (!b->start)
		b->start = b->node;
	else
	{
		parser_lexer_lstlast(b->start)->next = b->node;
		b->node->prev = parser_lexer_lstlast(b->start);
	}
	if (token == PIPE)
		b->str[b->i] = 2;
	else if (token == LESS_LESS || token == GREAT_GREAT)
		b->i++;
	else if (token == 0)
		b->i += b->j - b->i - 1;
}

void	parser_handle_double_quotes(t_parser_lexer_builder *b)
{
	char	*tmp;

	b->j = b->i + 1;
	while (b->str[b->j] && b->str[b->j] != '\"')
		b->j++;
	if (b->str[b->j] && b->str[b->j + 1] == '\"')
	{
		ft_strrep(&b->str, b->j, 1, "");
		b->j += 2;
		while (b->str[b->j] && b->str[b->j] != '\"')
			b->j++;
	}
	if (b->j - b->i > 1 && b->str[b->j] == '\"')
	{
		b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
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
	if (b->str[b->j] && b->str[b->j + 1] == '\'')
	{
		ft_strrep(&b->str, b->j, 1, "");
		b->j += 2;
		while (b->str[b->j] && b->str[b->j] != '\'')
			b->j++;
	}
	if (b->j - b->i > 1 && b->str[b->j] == '\'')
	{
		b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
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

void	parser_handle_tokens(t_parser_lexer_builder *b, char *str)
{
	if (str[b->i] == '\'')
		parser_handle_quotes(b);
	else if (str[b->i] == '\"')
		parser_handle_double_quotes(b);
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
