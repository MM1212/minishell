/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:22:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/30 10:25:05 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>

int	cmds_check_for_ns(char **str, int i)
{
	int	k;

	k = 0;
	if (str && str[i][k] == '-' && str[i][k + 1] == 'n')
	{
		k += 2;
		while (str[i][k])
		{
			if (str[i][k] != 'n')
				return (0);
			k++;
		}
		return (1);
	}
	return (0);
}

int	cmds_overrides_echo_cmd(int ac, char **args)
{
	int		i;
	bool	suppress_newline;

	(void)ac;
	i = 1;
	suppress_newline = false;
	if (args[i] != NULL && cmds_check_for_ns(args, i))
	{
		suppress_newline = true;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i++]);
		if (i < ac)
			ft_printf(" ");
	}
	if (!suppress_newline)
	{
		printf("\n");
	}
	return (0);
}
