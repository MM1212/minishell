/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 23:26:54 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <prompter/prompter.h>
#include <env/registry.h>
#include <errno.h>
#include <utils/error.h>
#include <shared.h>

static bool	check_limits(char *str)
{
	char	*max_str;

	max_str = ft_ltoa(LONG_MAX);
	if (ft_strcmp(str, max_str) < 0)
		return (free(max_str), \
			display_error("exit", "numeric argument required"), false);
	free(max_str);
	max_str = ft_ltoa(LONG_MIN);
	if (ft_strcmp(str, max_str) < 0)
		return (free(max_str), \
			display_error("exit", "numeric argument required"), false);
	free(max_str);
	return (true);
}

static bool	are_args_ok(int ac, char **av)
{
	size_t	idx;

	ac--;
	av++;
	if (ac == 0)
		return (true);
	if (ac > 1)
		return (display_error("exit", "too many arguments"), false);
	if (av[0] && ft_atoi(av[0]) == 0 && av[0][0] != '0')
		return (display_error("exit", "numeric argument required"), false);
	if (!check_limits(av[0]))
		return (false);
	idx = 0;
	while (av[0][idx])
	{
		if (!ft_isdigit(av[0][idx++]))
			return (display_error("exit", "numeric argument required"), false);
	}
	return (true);
}

void	cmds_overrides_exit_cmd(int ac, char **av, int *exit_code)
{
	char	*str;

	(void)ac;
	(void)av;
	if (!are_args_ok(ac, av))
		*exit_code = 2;
	else
		*exit_code = (unsigned char)ft_atol(av[1]);
	str = ft_itoa(*exit_code);
	(get_envp())->set("?", str);
	free(str);
	get_prompter()->keep_prompting = false;
}
