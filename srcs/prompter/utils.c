/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:00:07 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 20:33:58 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompter/prompter.h"
#include <env/registry.h>
#include <utils/colors.h>

void	prompter_get_prefix(char *prefix)
{
	char	*cwd;
	char	*home;
	char	*path;

	cwd = get_envp()->get_value("PWD");
	home = get_envp()->get_value("HOME");
	path = NULL;
	if (!cwd || !home)
	{
		ft_sprintf(prefix, 1024, "minishell> ");
		return ;
	}
	if (ft_strnstr(cwd, home, ft_strlen(home)) == cwd)
	{
		path = ft_strjoin("~", cwd + ft_strlen(home));
		cwd = path;
	}
	ft_sprintf(\
		prefix, 1024, \
		COLORS_LIGHT_GREEN"%s"COLORS_RESET":"\
		COLORS_LIGHT_BLUE"%s"COLORS_RESET"$ ", \
		get_envp()->get_value("USER"), cwd \
	);
	if (path)
		free(path);
}

bool	prompter_check_if_empty(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " ");
	if (ft_strlen(trimmed) == 0)
	{
		free(line);
		free(trimmed);
		return (false);
	}
	free(trimmed);
	return (true);
}
