/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:53:11 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 12:12:48 by martiper         ###   ########.fr       */
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
	display_error(path, "command not found");
	return (NULL);
}

static char	*env_path_search_path(char *exec, char **paths)
{
	char	path[1024];
	size_t	idx;

	idx = 0;
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
			return (ft_strdup(path));
		}
		idx++;
	}
	return (NULL);
}

char	*env_path_find_path(char *exec)
{
	char	**paths;
	char	*path;

	if (!exec)
		return (NULL);
	if (ft_strchr(exec, '/') != NULL)
		return (env_path_parse_exec_at_path(exec));
	paths = get_envp()->path->get_paths();
	if (!paths)
	{
		display_error(exec, "command not found");
		return (NULL);
	}
	path = env_path_search_path(exec, paths);
	ft_split_free(paths);
	if (path)
		return (path);
	else
		display_error(exec, "command not found");
	return (NULL);
}
