/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:08:09 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 22:16:01 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir/dir_fns.h"
#include <utils/error.h>

bool	dir_is_path_an_executable(char *path)
{
	struct stat	st;

	if (stat(path, &st) < 0)
	{
		perror("minishell: stat: ");
		return (false);
	}
	return ((st.st_mode & __S_IFMT) == __S_IFREG && (st.st_mode & S_IXUSR));
}

bool	dir_go_to_path(char *path)
{
	t_envp	*envp;
	char	*new_pwd;
	char	error_msg[256];

	envp = get_envp();
	if (!envp)
		return (false);
	if (!path)
		path = envp->get_value("HOME");
	if (chdir(path) < 0)
	{
		ft_sprintf(error_msg, 256, "cd: %s", path);
		display_error(error_msg, NULL);
		return (false);
	}
	envp->set("OLDPWD", envp->get_value("PWD"));
	new_pwd = getcwd(NULL, 0);
	envp->set("PWD", new_pwd);
	free(new_pwd);
	return (true);
}
