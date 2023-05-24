/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 14:55:16 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <dir/dir.h>
#include <errno.h>

int	cmds_overrides_cd_cmd(int ac, char **av)
{
	(void)ac;
	(void)av;
	return (0);
}

void	cmds_overrides_cd_cmd_on_execute(int ac, char **av, int exit_code)
{
	ac--;
	av++;
	(void)exit_code;
	if (ac != 1)
	{
		errno = EINVAL;
		return ;
	}
	get_dir()->go_to(av[0]);
}
