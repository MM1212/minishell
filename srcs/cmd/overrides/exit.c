/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 15:22:58 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <prompter/prompter.h>
#include <env/registry.h>
#include <errno.h>

int	cmds_overrides_exit_cmd(int ac, char **av)
{
	ft_printf("executing exit..\n");
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

void	cmds_overrides_exit_cmd_on_execute(int exit_code)
{
	char	*exit_str;

	ft_printf("executed exit with status of %d\n", exit_code);
	if (exit_code == -1)
	{
		errno = EINVAL;
		return ;
	}
	exit_str = ft_itoa(exit_code);
	get_envp()->set("?", exit_str);
	free(exit_str);
	get_prompter()->keep_prompting = false;

}
