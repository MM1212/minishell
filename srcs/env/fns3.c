/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:40:47 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 14:28:56 by martiper         ###   ########.fr       */
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

char	*env_registry_expand_arg(char *arg)
{
	char		*str;
	char		*var_name;
	size_t		idx;
	size_t		start;
	char		*var;

	str = ft_strdup(arg);
	idx = 0;
	while (str[idx])
	{
		if (str[idx++] != '$')
		{
			continue ;
		}
		start = idx;
		while (str[idx] && env_registry_is_var_char_valid(str[idx]))
			idx++;
		var_name = ft_substr(str, start, idx - start);
		var = get_envp()->get_value(var_name);
		free(var_name);
		setup_replace(&str, start - 1, idx - start + 1, var);
		idx = 0;
	}
	return (str);
}

bool	env_registry_is_var_char_valid(char c)
{
	return (!(c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
			|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
			|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
			|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
			|| c == '~' || c == '"' || c == '`' || c == '(' || c == ')'
			|| c == '$'
			|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*'));
}
