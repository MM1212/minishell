/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:48:08 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <dir/dir.h>
#include <errno.h>

int	cmds_overrides_cd_cmd(int ac, char **av)
{
	if (ac != 1)
	{
		errno = EINVAL;
		return (errno);
	}
	if (!get_dir()->go_to(av[0]))
		return (1);
	return (0);
}
