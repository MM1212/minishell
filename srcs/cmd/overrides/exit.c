/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:55:54 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <prompter/prompter.h>
#include <env/registry.h>
#include <errno.h>

int	cmds_overrides_exit_cmd(int ac, char **av)
{
	if (ac > 1)
	{
		errno = EINVAL;
		return (errno);
	}
	if (av[0] && ft_atoi(av[0]) == 0 && av[0][0] != '0')
	{
		errno = EINVAL;
		return (errno);
	}
	if (av[0])
		get_envp()->set("?", av[0]);
	get_prompter()->keep_prompting = false;
	return (0);
}
