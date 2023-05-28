/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:26:22 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 22:28:25 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include "env/var.h"
#include "env/registry_fns.h"

t_env_var	*env_build_var(char *name, char *value)
{
	t_env_var	*var;

	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}

static void	adjust_for_quotes(\
	char *equals_sign, char *entry, \
	size_t *start, size_t *len \
)
{
	*start = equals_sign - entry + 1;
	if (entry[*start] == '"' || entry[*start] == '\'' || entry[*start] == 4)
		(*start)++;
	*len = ft_strlen(entry) - *start;
	if (entry[*start + (*len) - 1] == '"' || entry[*start + (*len) - 1] == '\'' \
		|| entry[*start + (*len) - 1] == 4)
		(*len)--;
}

static bool	check_for_valid_name(char *name)
{
	size_t	idx;

	idx = 0;
	if (ft_atoi(name) != 0)
		return (false);
	while (name[idx])
	{
		if (!env_registry_is_var_char_valid(name[idx]))
		{
			return (false);
		}
		idx++;
	}
	return (true);
}

t_env_var	env_build_var_from_str(char *entry)
{
	t_env_var	var;
	char		*equals_sign;
	size_t		start;
	size_t		len;

	var = (t_env_var){NULL, NULL};
	equals_sign = ft_strchr(entry, '=');
	if (!equals_sign)
		var.name = ft_strdup(entry);
	else
		var.name = ft_substr(entry, 0, equals_sign - entry);
	if (!check_for_valid_name(var.name))
		return (free(var.name), (t_env_var){NULL, NULL});
	if (!equals_sign)
		return (var);
	adjust_for_quotes(equals_sign, entry, &start, &len);
	var.value = ft_substr(entry, start, len);
	if (!var.name || !var.value)
		return (free(var.name), free(var.value), (t_env_var){NULL, NULL});
	return (var);
}

void	env_delete_var(t_env_var *var)
{
	if (!var)
		return ;
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}
