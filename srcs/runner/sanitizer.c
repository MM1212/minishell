/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:01:47 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 15:07:42 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <env/registry.h>

static bool	handle_var_expanding(char **args, size_t idx)
{
	t_envp	*envp;
	char	*arg;

	envp = get_envp();
	if (args[idx][0] == '"')
		arg = ft_strdup(args[idx] + 1);
	else
		arg = ft_strdup(args[idx]);
	if (!arg)
		return (false);
	free(args[idx]);
	args[idx] = envp->expand_arg(arg);
	free(arg);
	return (true);
}

size_t	runner_sanitize_args(char **args)
{
	size_t	idx;
	char	*arg;

	idx = 1;
	while (args[idx])
	{
		if (args[idx][0] != '\'')
		{
			if (!handle_var_expanding(args, idx))
				return (false);
		}
		else
		{
			arg = ft_strdup(args[idx] + 1);
			if (!arg)
				return (0);
			free(args[idx]);
			args[idx] = arg;
		}
		idx++;
	}
	return (idx);
}
