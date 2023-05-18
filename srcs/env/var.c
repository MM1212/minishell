/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:26:22 by martiper          #+#    #+#             */
/*   Updated: 2023/05/18 14:06:40 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include "env/var.h"

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

t_env_var	env_build_var_from_str(char *entry)
{
	t_env_var	var;
	char		*equals_sign;

	var = (t_env_var){NULL, NULL};
	equals_sign = ft_strchr(entry, '=');
	if (!equals_sign)
		return (var);
	var.name = ft_substr(entry, 0, equals_sign - entry);
	var.value = ft_substr(entry, equals_sign - entry + 1, ft_strlen(entry));
	if (!var.name || !var.value)
	{
		if (var.name)
			free(var.name);
		if (var.value)
			free(var.value);
		return ((t_env_var){NULL, NULL});
	}
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

char	*env_var_to_string(t_env_var *var)
{
	char	*str;
	size_t	len;

	if (!var)
		return (NULL);
	len = ft_strlen(var->name) + ft_strlen(var->value) + 1;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_sprintf(\
		str, len + 1, \
		"%s=%s", \
		var->name, \
		var->value \
	);
	return (str);
}
