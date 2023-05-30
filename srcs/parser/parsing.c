/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:40 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/30 11:56:34 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

t_parser_lexer	*parser_handle_redirections(t_parser_lexer *saver, \
	t_parser_simple_cmds *node, t_parser_simple_cmds *start)
{
	t_parser_redirect_builder	b;

	b.returner = saver;
	if (saver->token > 1 && saver->token <= 5)
	{
		b.redirec = (t_parser_lexer *)ft_calloc(1, sizeof(t_parser_lexer));
		b.redirec->str = ft_strdup(saver->next->str);
		if (!b.redirec->str || !b.redirec)
			(parser_error_printer(saver, 0, 0, start));
		b.redirec->token = saver->token;
		b.redirec->next = NULL;
		b.redirec->prev = NULL;
		if (!node->redirections)
			node->redirections = b.redirec;
		else
			parser_ft_lexeradd_back(&node->redirections, b.redirec);
		b.i1 = saver->i;
		b.i2 = saver->next->i;
		b.returner = saver->next->next;
		node->num_redirections++;
	}
	return (b.returner);
}

int	parser_allocate_and_fill(t_parser_cmds_builder *b, t_parser_lexer **guide, \
	t_parser_lexer *saver)
{
	b->node->str = (char **)ft_calloc(b->amount + 1, sizeof(char *));
	if (!b->node->str)
		return (parser_error_printer(saver, 0, 0, b->start));
	b->amount = 0;
	b->node->redirections = NULL;
	while (b->saver && b->saver->token != PIPE)
	{
		b->saver = parser_handle_redirections(b->saver, b->node, b->start);
		if (!b->saver)
			break ;
		if (b->saver->token == 0)
		{
			b->node->str[b->amount++] = ft_strdup(b->saver->str);
			b->saver = b->saver->next;
		}
	}
	b->node->str[b->amount] = NULL;
	b->node->next = NULL;
	if (!b->start)
		b->start = b->node;
	else
		parser_cmds_lstlast(b->start)->next = b->node;
	if (*guide && (*guide)->token == PIPE)
		*guide = (*guide)->next;
	return (0);
}

t_parser_simple_cmds	*parser_build_commands(t_parser_lexer *guide)
{
	t_parser_lexer			*saver;
	t_parser_cmds_builder	b;

	saver = guide;
	b.start = NULL;
	b.amount = 0;
	while (guide)
	{
		b.saver = guide;
		b.node = ft_calloc(1, sizeof(t_parser_simple_cmds));
		if (!b.node)
			(parser_error_printer(saver, 0, 0, b.start));
		while (guide && guide->token != PIPE)
		{
			guide = guide->next;
			b.amount++;
		}
		if (parser_allocate_and_fill(&b, &guide, saver))
			return (NULL);
	}
	return (b.start);
}

t_parser_simple_cmds	*parser(char *str)
{
	t_parser_lexer			*start;
	t_parser_simple_cmds	*cmds;

	start = parser_build_lexer(str);
	if (!start)
		return (NULL);
	if (parser_check_errors(start, start, str))
		return (NULL);
	cmds = parser_build_commands(start);
	parser_clear_lexer(start);
	return (cmds);
}

#ifdef PARSER_TEST

int	main(void)
{
	char					*str;
	t_parser_simple_cmds	*cmds;

	str = ft_strdup(\
		"<< \"EOF\" > file");
	cmds = parser(str);
	if (!cmds)
		return (0);
	while (cmds)
	{
		printf("argument: %s\n", *cmds->str++);
		while (*cmds->str)
			printf("option: %s\n", *cmds->str++);
		if (cmds->redirections)
		{
			printf("redirections: %s\n", cmds->redirections->str);
			printf("token: %u\n", cmds->redirections->token);
		}
		printf("\n");
		cmds = cmds->next;
	}
	printf("%s, len: %zu\n", str, ft_strlen(str));
	free(str);
	return (0);
}
#endif
