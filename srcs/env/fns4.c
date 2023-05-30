/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:42:56 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 11:51:13 by martiper         ###   ########.fr       */
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

static void	expand_arg( \
	char **arg, \
	size_t	*idx \
)
{
	size_t		start;
	char		*var_name;
	char		*var_value;

	start = *idx;
	while ((*arg)[(*idx)] && env_registry_is_var_char_valid((*arg)[(*idx)]))
		(*idx)++;
	var_name = ft_substr((*arg), start, (*idx) - start);
	var_value = (get_envp())->get_value(var_name);
	setup_replace(arg, start - 1, \
		(*idx) - start + 1, var_value);
	(*idx) = start + ft_strlen(var_value) - 1;
	free(var_name);
}

void	env_registry_raw_expand_arg(char **arg)
{
	size_t						idx;

	idx = 0;
	while ((*arg)[idx])
	{
		if ((*arg)[idx++] != '$')
			continue ;
		if (!env_registry_is_var_char_valid((*arg)[idx]))
			continue ;
		expand_arg(arg, &idx);
	}
}
