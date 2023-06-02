/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/06/02 10:49:12 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <prompter/prompter.h>
#include <env/registry.h>
#include <errno.h>
#include <utils/error.h>
#include <shared.h>

typedef enum e_exit_status_types
{
	EXIT_STATUS_OK,
	EXIT_STATUS_WARN,
	EXIT_STATUS_ERR
}	t_exit_status_types;

static bool	check_limits(char *str)
{
	long long	nbr;

	nbr = ft_atol(str);
	if (nbr > INT_MAX)
		return (display_error("exit", "numeric argument i required"), false);
	if (nbr < INT_MIN)
		return (display_error("exit", "numeric argument o required"), false);
	return (true);
}

static t_exit_status_types	are_args_ok(int ac, char **av)
{
	size_t	idx;

	if (ac == 0)
		return (EXIT_STATUS_OK);
	if (ac > 1)
		return (display_error("exit", "too many arguments"), \
			EXIT_STATUS_ERR);
	if (av[0] && ft_atol(av[0]) == 0 && av[0][0] != '0')
		return (display_error("exit", "numeric argument required"), \
			EXIT_STATUS_WARN);
	if (!check_limits(av[0]))
		return (EXIT_STATUS_WARN);
	idx = 0;
	while (av[0][idx])
	{
		if (!ft_isdigit(av[0][idx++]))
			return (display_error("exit", "numeric argument required"), \
				EXIT_STATUS_WARN);
	}
	return (EXIT_STATUS_OK);
}

void	cmds_overrides_exit_cmd(int ac, char **av, int *exit_code)
{
	char				*str;
	t_exit_status_types	ok;

	ac--;
	av++;
	ok = are_args_ok(ac, av);
	if (ok > 0)
		*exit_code = 2;
	else
		*exit_code = (unsigned char)ft_atoi(av[0]);
	if (ok == EXIT_STATUS_ERR)
		return ;
	str = ft_itoa(*exit_code);
	(get_envp())->set("?", str);
	free(str);
	get_prompter()->keep_prompting = false;
}
