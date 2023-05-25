/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 08:39:54 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 11:34:27 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>

char	**whileloop_del_var(char **envp, char **modified_envp, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (envp[++i] != NULL)
	{
		if (!(ft_strncmp(envp[i], str, equal_sign(envp[i]) - 1) == 0
				&& str[equal_sign(envp[i])] == '\0'
				&& envp[i][ft_strlen(str)] == '='))
		{
			modified_envp[++j] = ft_strdup(envp[i]);
			if (modified_envp[j] == NULL)
			{
				free_arr(modified_envp);
				return (modified_envp);
			}
		}
	}
	return (modified_envp);
}

char	**del_var(char **envp, char *str)
{
	char	**modified_envp;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	modified_envp = ft_calloc(sizeof(char *), i + 1);
	if (!modified_envp)
		return (NULL);
	modified_envp = whileloop_del_var(envp, modified_envp, str);
	return (modified_envp);
}

int	unset_error(char **av)
{
	int		i;

	i = -1;
	if (!av[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return (1);
	}
	while (av[1][++i])
	{
		if (av[1][i] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(av[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
	}
	if (equal_sign(av[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	mini_unset(NEED STRUCT WITH ENVP, char **av)
{
	char	**modified_envp;

	if (unset_error(av) == 1)
		return (1);
	else
	{
		modified_envp = del_var(NEED STRUCT WITH ENVP: envp, av[1]);
		FREE ARRAY FUNCTION HERE -> free_array(NEED STRUCT WITH ENVP: envp);
		NEED STRUCT WITH ENVP: envp = modified_envp;
	}
	return (0);
}
