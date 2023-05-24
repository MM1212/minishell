/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:16 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/24 13:43:14 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parsing.h"

t_parser_lexer	*parser_ft_lexerclear_one(t_parser_lexer **lst)
{
	if (!lst || !(*lst))
		return (NULL);
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

t_parser_simple_cmds	*parser_ft_simple_cmds_clear_one(\
	t_parser_simple_cmds **lst)
{
	int				i;

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
	parser_clear_lexer((*lst)->redirections);
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
	if (!str)
		printf("syntax error near unexpected token '%s'\n", guide->str);
	else if (!str && !guide)
		printf("memory allocation error\n");
	else
		printf("syntax error near unexpected token %s\n", str);
	parser_clear_lexer(start);
	parser_clear_cmds(cmds);
	return (1);
}

int	parser_check_errors(t_parser_lexer *start, t_parser_lexer *guide, char *str)
{
	while (guide)
	{
		if (guide->token > 0 && (!guide->next || (guide->next && \
			!guide->next->str[0])))
			return (parser_error_printer(start, guide, 0, 0));
		if (guide->token != 0 && (guide->token == guide->next->token))
			return (parser_error_printer(start, guide, 0, 0));
		guide = guide->next;
	}
	return (parser_check_quotes(start, guide, str));
}
