/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:22:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/24 15:48:14 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>

int	cmds_overrides_echo_cmd(int ac, char **args)
{
	int		i;
	bool	suppressNewline;

	(void)ac;
	i = 1;
	suppressNewline = false;
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		suppressNewline = true;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
		{
			printf(" ");
		}
		i++;
	}
	if (!suppressNewline)
	{
		printf("\n");
	}
	return (0);
}
