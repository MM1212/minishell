/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:08:09 by martiper          #+#    #+#             */
/*   Updated: 2023/06/02 11:04:19 by martiper         ###   ########.fr       */
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

static bool	grab_home(char **str, t_env_var *home)
{
	size_t	idx;

	idx = 0;
	if (!str || !*str)
		return (display_error("cd", "HOME not set"), false);
	while (str[0][idx])
	{
		if (str[0][idx] == '~')
		{
			if (!home)
				return (display_error("cd", "HOME not set"), false);
			ft_strrep(str, idx, 1, home->value);
			idx += ft_strlen(home->value);
		}
		else
			idx++;
	}
	return (true);
}

static void	set_path_to_envp(t_envp *envp)
{
	char	*new_pwd;

	envp->set("OLDPWD", envp->get_value("PWD"));
	new_pwd = getcwd(NULL, 0);
	envp->set("PWD", new_pwd);
	free(new_pwd);
}

bool	dir_go_to_path(char *path)
{
	t_envp	*envp;
	char	error_msg[256];

	envp = get_envp();
	if (!envp)
		return (false);
	if (!path)
		path = envp->get_value("HOME");
	path = ft_strdup(path);
	if (!grab_home(&path, envp->get("HOME")))
		return (free(path), false);
	if (chdir(path) < 0)
	{
		ft_sprintf(error_msg, 256, "cd: %s", path);
		display_error(error_msg, NULL);
		return (free(path), false);
	}
	free(path);
	if (envp->is_set("PWD"))
		set_path_to_envp(envp);
	else
		envp->set("OLDPWD", NULL);
	return (true);
}
