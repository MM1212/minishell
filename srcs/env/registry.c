/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:32:55 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 11:46:35 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/registry.h"
#include "env/registry_fns.h"
#include "env/path/path_fns.h"
#include <context/context.h>

static size_t	env_registry_get_size(void)
{
	t_env_registry	*registry;
	size_t			size;
	t_list			*iter;

	registry = get_envp();
	if (!registry)
		return (0);
	iter = registry->vars;
	size = 0;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	return (size);
}

static t_env_registry	*env_registry_create(void)
{
	t_env_registry	*envp;

	envp = ft_calloc(1, sizeof(t_env_registry));
	if (!envp)
		return (NULL);
	envp->vars = NULL;
	envp->size = env_registry_get_size;
	envp->get = env_registry_get_var;
	envp->get_value = env_registry_get_var_value;
	envp->add = env_registry_add_var;
	envp->set = env_registry_set_var;
	envp->unset = env_registry_unset_var;
	envp->get_env = env_registry_get_env;
	envp->is_set = env_registry_is_var_set;
	envp->print = env_registry_print;
	envp->init = env_registry_init;
	envp->expand_arg = env_registry_expand_arg;
	envp->raw_expand_arg = env_registry_raw_expand_arg;
	envp->build_from_str = env_build_var_from_str;
	envp->path = env_path_create();
	if (!envp->path)
		return (free(envp), NULL);
	return (envp);
}

static void	env_registry_destroy(t_env_registry *registry)
{
	if (!registry)
		return ;
	ft_lstclear(\
		&registry->vars, \
		(void (*)(void *))env_delete_var \
	);
	free(registry->path);
	free(registry);
}

t_envp	*get_envp(void)
{
	return (
		get_context(\
			CONTEXT_ID_ENV_REGISTRY, \
			(t_context_construct_fn)env_registry_create, \
			(t_context_destruct_fn)env_registry_destroy \
		)
	);
}
