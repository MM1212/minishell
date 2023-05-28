/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:49:32 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 22:17:28 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir/dir_fns.h"

/*
	Relative to HOME (which adds a ~ at the beginning of the path)

*/
char	*dir_get_relative_path(char *buffer, size_t size)
{
	char	*home;
	char	*pwd;

	home = get_envp()->get_value("HOME");
	pwd = get_envp()->get_value("PWD");
	if (!pwd || !home)
		ft_sprintf(buffer, size, "/");
	else if (ft_strnstr(pwd, home, ft_strlen(home)) == pwd)
		ft_sprintf(buffer, size, "~%s", pwd + ft_strlen(home));
	else
		ft_sprintf(buffer, size, "%s", pwd);
	return (buffer);
}

char	*dir_get_full_path(void)
{
	return (getcwd(NULL, 0));
}

char	*dir_get_home_path(void)
{
	t_envp	*envp;

	envp = get_envp();
	if (!envp)
		return (NULL);
	return (envp->get_value("HOME"));
}

bool	dir_is_path_a_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) < 0)
	{
		perror("minishell: stat: ");
		return (false);
	}
	return ((st.st_mode & __S_IFMT) == __S_IFDIR);
}

bool	dir_is_path_a_file(char *path)
{
	struct stat	st;

	if (stat(path, &st) < 0)
	{
		perror("minishell: stat: ");
		return (false);
	}
	return ((st.st_mode & __S_IFMT) == __S_IFREG);
}
