/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:42:34 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 16:57:23 by martiper         ###   ########.fr       */
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

static bool	on_arg(
	char **av, \
	size_t idx, \
	char **key, \
	t_envp *envp
)
{
	char	*str;
	size_t	str_len;

	str = av[idx];
	str_len = ft_strlen(str);
	if (!*key)
	{
		if (str_len == 0 || !ft_strchr(str, '='))
		{
			*key = NULL;
			return (false);
		}
		*key = ft_substr(str, 0, ft_strchr(str, '=') - str);
		if (str[str_len - 1] == '=')
			return (false);
		str += ft_strlen(*key) + 1;
	}
	envp->set(*key, str);
	free(*key);
	*key = NULL;
	return (true);
}

void	cmds_overrides_export_cmd(int ac, char **av, int *exit_code)
{
	size_t		idx;
	char		*key;
	t_envp		*envp;

	ac--;
	av++;
	envp = get_envp();
	(void)exit_code;
	if (ac == 0)
		return (show_available_vars());
	idx = 0;
	key = NULL;
	while (av[idx])
	{
		if (!on_arg(av, idx, &key, envp))
		{
			idx++;
			continue ;
		}
		idx++;
	}
}
