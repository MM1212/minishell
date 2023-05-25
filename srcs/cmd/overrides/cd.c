/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 13:54:46 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <dir/dir.h>
#include <errno.h>

void	cmds_overrides_cd_cmd(int ac, char **av, int *exit_code)
{
	ac--;
	av++;
	if (ac != 1)
	{
		*exit_code = EINVAL;
		return ;
	}
	get_dir()->go_to(av[0]);
}
