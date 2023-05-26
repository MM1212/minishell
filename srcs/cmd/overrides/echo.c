/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:22:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 17:22:37 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>

int	cmds_overrides_echo_cmd(int ac, char **args)
{
	int		i;
	bool	suppress_newline;

	(void)ac;
	i = 1;
	suppress_newline = false;
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		suppress_newline = true;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i++]);
		if (i > 2)
			ft_printf(" ");
	}
	if (!suppress_newline)
	{
		printf("\n");
	}
	return (0);
}
