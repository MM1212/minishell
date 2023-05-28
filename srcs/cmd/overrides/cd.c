/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 22:47:03 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <dir/dir.h>
#include <errno.h>
#include <utils/error.h>

void	cmds_overrides_cd_cmd(int ac, char **av, int *exit_code)
{
	ac--;
	av++;
	if (ac > 1)
	{
		*exit_code = 1;
		display_error("cd", "too many arguments");
		return ;
	}
	if (!get_dir()->go_to(av[0]))
		*exit_code = 1;
}
