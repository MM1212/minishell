/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 22:13:28 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <dir/dir.h>
#include <errno.h>
#include <utils/error.h>

static void	output_err(char *err, int *exit_code)
{
	*exit_code = 1;
	display_error("cd", err);
}

static bool	grab_home(char **str, t_env_var *home, int *exit_code)
{
	size_t	idx;

	idx = 0;
	while (str[0][idx])
	{
		if (str[0][idx] == '~')
		{
			if (!home)
				return (output_err("HOME not set", exit_code), false);
			ft_strrep(str, idx, 1, home->value);
			idx += ft_strlen(home->value);
		}
		else
			idx++;
	}
	return (true);
}

void	cmds_overrides_cd_cmd(int ac, char **av, int *exit_code)
{
	t_env_var	*home;

	ac--;
	av++;
	if (ac > 1)
	{
		*exit_code = 1;
		display_error("cd", "too many arguments");
		return ;
	}
	home = get_envp()->get("HOME");
	if (ac == 0)
	{
		if (!home)
			return (output_err("HOME not set", exit_code));
		get_dir()->go_to(home->value);
		return ;
	}
	if (!grab_home(av, home, exit_code))
		return ;
	get_dir()->go_to(av[0]);
}
