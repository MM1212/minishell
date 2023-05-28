/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:46:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/29 00:07:19 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir/dir.h"
#include "dir/dir_fns.h"
#include <context/context.h>

static t_dir	*dir_create(void)
{
	t_dir	*dir;
	char	*cwd;

	dir = ft_calloc(1, sizeof(t_dir));
	if (!dir)
		return (NULL);
	dir->get_relative = dir_get_relative_path;
	dir->get_full = dir_get_full_path;
	dir->get_home = dir_get_home_path;
	dir->is_dir = dir_is_path_a_dir;
	dir->is_file = dir_is_path_a_file;
	dir->is_executable = dir_is_path_an_executable;
	dir->go_to = dir_go_to_path;
	cwd = dir->get_full();
	(get_envp())->set("PWD", cwd);
	(get_envp())->set("OLDPWD", NULL);
	free(cwd);
	return (dir);
}

t_dir	*get_dir(void)
{
	return (
		get_context(\
			CONTEXT_ID_DIRECTORY_MANAGER, \
			(void *(*)(void))dir_create, \
			free \
		)
	);
}
