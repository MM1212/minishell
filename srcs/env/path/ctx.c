/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:51:45 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 13:26:00 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/path/path_fns.h"
#include "env/registry.h"

static char	*env_path_get(void)
{
	t_envp	*envp;

	envp = get_envp();
	if (!envp)
		return (NULL);
	return (envp->get_value("PATH"));
}

t_env_path	*env_path_create(void)
{
	t_env_path	*path;

	path = ft_calloc(1, sizeof(t_env_path));
	if (!path)
		return (NULL);
	path->get = env_path_get;
	path->get_paths = env_path_get_paths;
	path->find_path = env_path_find_path;
	return (path);
}
