/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 04:28:59 by martiper          #+#    #+#             */
/*   Updated: 2023/05/21 04:43:22 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: DONT FORGET TO REMOVE!!!!!!!!!

#include "cmd/overrides.h"
#include <env/registry.h>
#include <errno.h>

int	cmds_overrides_internal_expand_cmd(int ac, char **av)
{
	char	*expanded;

	if (ac != 1)
	{
		errno = 1;
		return (errno);
	}
	expanded = get_envp()->expand_arg(av[0]);
	ft_printf("Got: '%s' and expanded to '%s'\n", av[0], expanded);
	free(expanded);
	return (0);
}
