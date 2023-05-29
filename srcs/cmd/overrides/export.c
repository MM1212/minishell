/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:42:34 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/29 11:31:51 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>
#include <env/registry.h>
#include <utils/error.h>

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

static void	show_error(char *param)
{
	char	error_msg[512];

	ft_sprintf(error_msg, 512, "'%s': not a valid identifier", param);
	display_error("export", error_msg);
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
		var = envp->build_from_str(av[idx]);
		if (var.name != NULL)
		{
			envp->set(var.name, var.value);
			free(var.name);
			free(var.value);
		}
		else
			show_error(av[idx]);
		idx++;
	}
}
