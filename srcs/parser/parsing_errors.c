/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:16 by diogpere          #+#    #+#             */
/*   Updated: 2023/06/02 14:05:57 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

int	parser_go_forward(char *str, char c, int *i, int *counter)
{
	if (str[*i] == c)
	{
		*counter += 1;
		*i += 1;
	}
	while (str[*i] && str[*i] != c)
		*i += 1;
	if (!str[*i])
		return (1);
	else if (str[*i] == c)
	{
		*counter += 1;
		*i += 1;
	}
	return (0);
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
		{
			if (parser_go_forward(str, '\"', &i, &count_double))
				break ;
		}
		if (str[i] == '\'')
			if (parser_go_forward(str, '\'', &i, &count_single))
				break ;
		if (!str[i])
			break ;
	}
	start = 0;
	guide = 0;
	// if (count_double % 2 != 0)
	// 	return (parser_error_printer(start, guide, "\"", 0));
	// else if (count_single % 2 != 0)
	// 	return (parser_error_printer(start, guide, "\'", 0));
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
	int				pairs;
	int				i;
	char			token;
	t_parser_lexer	*saver;

	pairs = 0;
	saver = guide;
	while (saver && saver->token != 0 && (saver->str[0] == guide->str[0] \
		|| saver->token == guide->token))
	{
		*count += 1;
		saver = saver->next;
	}
	token = guide->str[0];
	pairs = 0;
	i = -1;
	while (guide->str[++i])
	{
		if (guide->str[i] == '\"')
			pairs++;
	}
	i = 0;
	printf("pairs: %d\n", pairs);
	printf("count: %d\n", *count);
	while (guide->str[++i])
	{
		if (guide->str[i] != token || guide->str[i] != '|' || \
			guide->str[i] != '<' || guide->str[i] != '>' || pairs % 2 == 0)
		{
			*innercount = 0;
			break ;
		}
		else
			*innercount += 1;
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
			{
				printf("in here\n");
				return (parser_error_printer(start, guide, 0, 0));
			}

		count = 0;
		innercount = 0;
		check_tokens(guide, &innercount, &count);
		if (count > 1 || innercount > 1)
		{
			printf("in here\n");
			return (parser_error_printer(start, guide, 0, 0));
		}

		guide = guide->next;
	}
	return (parser_check_quotes(start, guide, str));
}
