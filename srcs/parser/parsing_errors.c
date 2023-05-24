/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:16 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/24 16:21:00 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

t_parser_simple_cmds	*parser_ft_simple_cmds_clear_one(\
	t_parser_simple_cmds **lst)
{
	int				i;
	t_parser_lexer	*redirections;

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
	redirections = (*lst)->redirections;
	parser_ft_lexerclear_one(&redirections);
	free(*lst);
	*lst = NULL;
	return (NULL);
}

int	parser_check_quotes(t_parser_lexer *start, t_parser_lexer *guide, char *str)
{
	int	i;
	int	count_double;
	int	count_single;

	i = -1;
	count_double = 0;
	count_single = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			count_double++;
		else if (str[i] == '\'')
			count_single++;
	}
	if (count_double % 2 != 0)
		return (parser_error_printer(start, guide, "\"", 0));
	else if (count_single % 2 != 0)
		return (parser_error_printer(start, guide, "\'", 0));
	return (0);
}

int	parser_error_printer(t_parser_lexer *start, t_parser_lexer \
	*guide, char *str, t_parser_simple_cmds *cmds)
{
	if (!str && guide)
		printf("syntax error near unexpected token '%s'\n", guide->str);
	else if (!str && !guide)
		printf("memory allocation error\n");
	else
		printf("syntax error near unexpected token %s\n", str);
	parser_clear_lexer(start);
	parser_clear_cmds(cmds);
	return (1);
}

void	check_tokens(t_parser_lexer *guide, int *innercount, int *count)
{
	int				i;
	char			token;
	t_parser_lexer	*saver;

	i = 0;
	token = guide->str[0];
	while (guide->str[++i])
	{
		if (guide->str[i] != token)
		{
			*innercount = 0;
			break ;
		}
		else
			*innercount += 1;
	}
	saver = guide;
	while (saver && saver->token != 0 && (saver->str[0] == guide->str[0] \
		|| saver->token == guide->token))
	{
		*count += 1;
		saver = saver->next;
	}
}

int	parser_check_errors(t_parser_lexer *start, t_parser_lexer *guide, char *str)
{
	int				count;
	int				innercount;

	while (guide)
	{
		if (guide->token > 0 && (!guide->next || (guide->next && \
			!guide->next->str[0])))
			return (parser_error_printer(start, guide, 0, 0));
		count = 0;
		innercount = 0;
		check_tokens(guide, &innercount, &count);
		if (count > 1 || innercount > 1)
			return (parser_error_printer(start, guide, 0, 0));
		guide = guide->next;
	}
	return (parser_check_quotes(start, guide, str));
}
