/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:40:47 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 15:25:46 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/registry.h"
#include "env/registry_fns.h"

static void	setup_replace(\
	char **str, \
	size_t start, \
	size_t len, \
	char *replace \
)
{
	if (!replace)
		ft_strrep(str, start, len, "");
	else
		ft_strrep(str, start, len, replace);
}

typedef enum e_env_var_expansion_state
{
	ENV_VAR_EXPANSION_STATE_NONE,
	ENV_VAR_EXPANSION_STATE_SINGLE_QUOTE,
	ENV_VAR_EXPANSION_STATE_DOUBLE_QUOTE,
}	t_env_var_expansion_state;

static void	select_state(\
	char c, \
	t_env_var_expansion_state *state \
)
{
	if (c == '\'')
		*state = ENV_VAR_EXPANSION_STATE_SINGLE_QUOTE;
	else if (c == '\"')
		*state = ENV_VAR_EXPANSION_STATE_DOUBLE_QUOTE;
	else if (c == 4)
		*state = ENV_VAR_EXPANSION_STATE_NONE;
}

void	env_registry_remove_quotes(char **str)
{
	size_t	idx;

	idx = 0;
	while ((*str)[idx])
	{
		if ((*str)[idx] == '\'' || (*str)[idx] == '\"' || (*str)[idx] == 4)
			ft_strrep(str, idx, 1, "");
		else
			idx++;
	}
}

void	env_registry_expand_arg(char **arg)
{
	char						*var_name;
	size_t						idx;
	size_t						start;
	t_env_var_expansion_state	state;

	idx = 0;
	state = ENV_VAR_EXPANSION_STATE_NONE;
	while ((*arg)[idx])
	{
		select_state((*arg)[idx], &state);
		if ((*arg)[idx++] != '$' || \
			state == ENV_VAR_EXPANSION_STATE_SINGLE_QUOTE)
		{
			continue ;
		}
		start = idx;
		while ((*arg)[idx] && env_registry_is_var_char_valid((*arg)[idx]))
			idx++;
		var_name = ft_substr((*arg), start, idx - start);
		setup_replace(arg, start - 1, \
			idx - start + 1, get_envp()->get_value(var_name));
		idx = start + ft_strlen(get_envp()->get_value(var_name)) - 1;
		free(var_name);
	}
	env_registry_remove_quotes(arg);
}

bool	env_registry_is_var_char_valid(char c)
{
	return (!(c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
			|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
			|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
			|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
			|| c == '~' || c == '"' || c == '`' || c == '(' || c == ')'
			|| c == '$' || c == 4
			|| c == '=' || c == '-' || c == '&' || c == '*'));
}
