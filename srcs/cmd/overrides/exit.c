/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 13:53:53 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <prompter/prompter.h>
#include <env/registry.h>
#include <errno.h>

int	cmds_overrides_exit_cmd(int ac, char **av)
{
	ac--;
	av++;
	if (ac > 1)
	{
		return (-1);
	}
	if (av[0] && ft_atoi(av[0]) == 0 && av[0][0] != '0')
	{
		return (-1);
	}
	if (ft_atoi(av[0]) < 0)
	{
		return (-1);
	}
	return (ft_atoi(av[0]));
}

void	cmds_overrides_exit_cmd_on_execute(int ac, char **av, int *exit_code)
{
	(void)ac;
	(void)av;
	if (*exit_code == -1)
	{
		*exit_code = EINVAL;
		return ;
	}
	get_prompter()->keep_prompting = false;
}
