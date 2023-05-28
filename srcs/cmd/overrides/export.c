/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:42:34 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/28 22:58:39 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>
#include <env/registry.h>
#include <utils/error.h>

static void	*map(void *content)
{
	return (content);
}

static int	sort_vars(t_env_var *a, t_env_var *b)
{
	return (ft_strcmp(a->name, b->name));
}

int	cmds_overrides_export_show_available_vars(int ac, char **av)
{
	t_list		*vars;
	t_env_var	*var;

	ac--;
	av++;
	if (ac > 0)
		return (0);
	vars = ft_lstmap(get_envp()->vars, map, (void (*)(void *))env_delete_var);
	if (!vars)
		return (1);
	ft_lstsort(vars, (int (*)(void *, void *))sort_vars);
	while (vars)
	{
		var = vars->content;
		if (!var->value)
			ft_printf("declare -x %s\n", var->name);
		else
			ft_printf("declare -x %s=\"%s\"\n", var->name, var->value);
		vars = vars->next;
	}
	ft_lstclear(&vars, NULL);
	return (0);
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
		return ;
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
