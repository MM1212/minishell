/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:42:34 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/25 11:34:10 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <shared.h>

char	**whileloop_add_var(char **envp, char **modified_envp, char *str)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (envp[i + 1] == NULL)
		{
			modified_envp[i] = ft_strdup(str);
			modified_envp[i + 1] = ft_strdup(envp[i]);
		}
		else
			modified_envp[i] = ft_strdup(envp[i]);
		if (modified_envp[i] == NULL)
		{
			// free array(modified_envp);
			return (modified_envp);
		}
	}
	return (modified_envp);
}

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
	}
	return (str);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (1);
}

size_t	equal_sign(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (i + 1);
	return (0);
}

char	**add_var(char **envp, char *str)
{
	char	**modified_envp;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (envp[i] != NULL)
		i++;
	modified_envp = ft_calloc(sizeof(char *), i + 2);
	if (!modified_envp)
		return (NULL);
	whileloop_add_var(envp, modified_envp, str);
	return (modified_envp);
}

int	variable_exist(NEED STRUCT WITH ENVP, char *str)
{
	int	i;

	i = -1;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (NEED STRUCT WITH ENVP: envp[++i])
	{
		if (ft_strncmp(NEED STRUCT WITH ENVP: envp[i],
				str, equal_sign(NEED STRUCT WITH ENVP: envp[i])) == 0)
		{
			free(NEED STRUCT WITH ENVP: envp[i]);
			NEED STRUCT WITH ENVP: envp[i] = ft_strdup(str);
			return (1);
		}
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = -1;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (1);
	if (str[0] == '=')
		return (export_error(str));
	while (str[++i] != '=')
		if (check_valid_identifier(str[i]))
			return (export_error(str));
	return (0);
}

int	cmds_overrides_export_cmd(int ac, char **av)
{
	int		i;
	char	**tmp;

	if (!av[1] || !av[1][0])
		cmds_overrides_env_cmd(ac, av);
	else
	{
		i = 0;
		while (av[++i])
		{
			if (check_parameter(av[i]) == 0 \
				&& variable_exist(NEED STRUCT WITH ENVP, av[i]) == 0)
			{
				if (av[i])
				{
					tmp = add_var(NEED STRUCT WITH ENVP: envp, av[i]);
					FREE ARRAY FUNCTION HERE -> free_array(NEED STRUCT WITH ENVP: envp);
					NEED STRUCT WITH ENVP: envp = tmp;
				}
			}

		}
	}
	return (0);
}
