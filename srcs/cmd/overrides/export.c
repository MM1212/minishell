/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:42:34 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 22:57:18 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>
#include <env/registry.h>

static void	show_available_vars(void)
{
	char	**vars;
	size_t	idx;

	idx = 0;
	vars = get_envp()->get_env();
	if (!vars)
		return ;
	while (vars[idx])
		ft_printf("declare -x \"%s\"\n", vars[idx++]);
	ft_split_free(vars);
}

void	cmds_overrides_export_cmd(int ac, char **av, int *exit_code)
{
	size_t		idx;
	t_envp		*envp;
	t_env_var	var;

	ac--;
	av++;
	envp = get_envp();
	(void)exit_code;
	if (ac == 0)
		return (show_available_vars());
	idx = 0;
	while (av[idx])
	{
		ft_printf("building from str: %s\n", av[idx]);
		var = envp->build_from_str(av[idx]);
		if (var.name != NULL)
		{
			envp->set(var.name, var.value);
			free(var.name);
			free(var.value);
		}
		idx++;
	}
}
