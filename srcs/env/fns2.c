/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:15:54 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 17:22:28 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/registry.h"
#include "env/registry_fns.h"

bool	env_registry_init(char **envp)
{
	t_env_registry	*registry;
	t_env_var		var;
	size_t			idx;

	idx = 0;
	registry = get_envp();
	if (!registry)
		return (false);
	while (envp[idx])
	{
		var = env_build_var_from_str(envp[idx]);
		if (!var.name)
			return (false);
		registry->add(var.name, var.value);
		idx++;
	}
	registry->set("?", "0");
	return (true);
}

char	**env_registry_get_env(void)
{
	t_env_registry	*registry;
	t_list			*iter;
	char			**arr;
	size_t			idx;

	registry = get_envp();
	if (!registry)
		return (NULL);
	arr = ft_calloc(registry->size() + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	iter = registry->vars;
	idx = 0;
	while (iter)
	{
		arr[idx++] = env_var_to_string(iter->content);
		if (!arr[idx - 1])
		{
			ft_split_free(arr);
			return (NULL);
		}
		iter = iter->next;
	}
	return (arr);
}

void	env_registry_print(void)
{
	t_env_registry	*registry;
	char			**env;
	size_t			idx;

	registry = get_envp();
	if (!registry)
		return ;
	idx = 0;
	env = registry->get_env();
	if (!env)
		return ;
	while (env[idx])
		ft_printf("%s\n", env[idx++]);
	ft_split_free(env);
}

char	*env_registry_get_var_value(char *name)
{
	t_env_registry	*registry;
	t_env_var		*var;

	registry = get_envp();
	if (!registry)
		return (NULL);
	var = registry->get(name);
	if (var)
		return (var->value);
	return (NULL);
}
