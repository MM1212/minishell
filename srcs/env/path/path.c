/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:53:11 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:26:05 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/path/path_fns.h"
#include "env/registry.h"
#include <utils/error.h>
#include <dir/dir.h>

char	**env_path_get_paths(void)
{
	t_envp	*envp;
	char	**paths;

	envp = get_envp();
	if (!envp)
		return (NULL);
	paths = ft_split(envp->get_value("PATH"), ":");
	return (paths);
}

static char	*env_path_parse_exec_at_path(char *path)
{
	char	final_path[1024];

	if (path[0] == '/' || path[0] == '.')
		ft_sprintf(final_path, 1024, "%s", path);
	else
		ft_sprintf(final_path, 1024, "./%s", path);
	if (\
		access(final_path, F_OK) == 0 && \
		get_dir()->is_executable(final_path)
	)
	{
		return (ft_strdup(final_path));
	}
	return (NULL);
}

char	*env_path_find_path(char *exec)
{
	char	**paths;
	char	path[1024];
	size_t	idx;
	bool	found;

	if (ft_strchr(exec, '/') != NULL)
		return (env_path_parse_exec_at_path(exec));
	paths = get_envp()->path->get_paths();
	if (!paths)
		return (NULL);
	idx = 0;
	found = false;
	while (paths[idx])
	{
		if (ft_str_endswith(paths[idx], "/"))
			ft_sprintf(path, 1024, "%s%s", paths[idx], exec);
		else
			ft_sprintf(path, 1024, "%s/%s", paths[idx], exec);
		if (\
			access(path, F_OK) == 0 && \
			get_dir()->is_executable(path)
		)
		{
			found = true;
			break ;
		}
		idx++;
	}
	ft_split_free(paths);
	if (found)
		return (ft_strdup(path));
	else
		display_error(exec);
	return (NULL);
}
