/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 08:39:54 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 12:46:35 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>
#include <env/registry.h>

void	cmds_overrides_unset_cmd(int ac, char **av, int *exit_code)
{
	size_t	idx;

	(void)exit_code;
	ac--;
	av++;
	idx = 0;
	while (av[idx])
		get_envp()->unset(av[idx++]);
}
