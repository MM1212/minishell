/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:43:20 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 11:29:38 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/registry.h"
#include "env/registry_fns.h"

t_env_var	*env_registry_get_var(char *name)
{
	t_env_registry	*registry;
	t_list			*iter;
	t_env_var		*var;

	registry = get_envp();
	if (!registry)
		return (NULL);
	iter = registry->vars;
	while (iter)
	{
		var = iter->content;
		if (ft_strcmp(var->name, name) == 0)
			return (var);
		iter = iter->next;
	}
	return (NULL);
}

bool	env_registry_add_var(char *name, char *value)
{
	t_env_registry	*registry;
	t_list			*node;
	t_env_var		*var;

	registry = get_envp();
	if (!registry)
		return (false);
	if (registry->is_set(name))
		return (false);
	var = env_build_var(name, value);
	if (!var)
		return (false);
	node = ft_lstnew(var);
	if (!node)
	{
		env_delete_var(var);
		return (false);
	}
	ft_lstadd_back(&registry->vars, node);
	return (true);
}

void	env_registry_set_var(char *name, char *value)
{
	t_env_registry	*registry;
	t_env_var		*var;

	registry = get_envp();
	if (!registry)
		return ;
	var = registry->get(name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
	else
		registry->add(ft_strdup(name), ft_strdup(value));
}

bool	env_registry_unset_var(char *name)
{
	t_env_registry	*registry;
	t_list			*iter;
	t_env_var		*var;

	registry = get_envp();
	if (!registry)
		return (false);
	iter = registry->vars;
	while (iter)
	{
		var = iter->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			ft_lstremove(\
				&registry->vars, \
				iter, \
				(void (*)(void *))env_delete_var \
			);
			return (true);
		}
		iter = iter->next;
	}
	return (false);
}

bool	env_registry_is_var_set(char *name)
{
	t_env_registry	*registry;
	t_list			*iter;
	t_env_var		*var;

	registry = get_envp();
	if (!registry)
		return (false);
	iter = registry->vars;
	while (iter)
	{
		var = iter->content;
		if (ft_strcmp(var->name, name) == 0)
			return (true);
		iter = iter->next;
	}
	return (false);
}
