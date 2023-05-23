/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 15:20:26 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <env/registry.h>
#include <errno.h>

int	cmds_overrides_env_cmd(int ac, char **av)
{
	ac--;
	(void)av;
	if (ac > 0)
	{
		errno = 1;
		return (errno);
	}
	get_envp()->print();
	return (0);
}
