/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:49:14 by martiper          #+#    #+#             */
/*   Updated: 2023/05/18 13:55:52 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompter/prompter.h"
#include <context/context.h>
#include <utils/colors.h>
#include <log/log.h>
#include <env/registry.h>

static void prompter_get_prefix(char *prefix)
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
		COLORS_LIGHT_GREEN"%s"COLORS_RESET":"COLORS_LIGHT_BLUE"%s"COLORS_RESET"$ ", \
		get_envp()->get_value("USER"), \
		cwd \
	);
	if (path)
		free(path);
}

static void	prompter_prompt(void)
{
	char	*line;
	char	prefix[1024];

	prompter_get_prefix(prefix);
	line = readline(prefix);
	if (!line || line[0] == '\n' || line[0] == '\0')
		return ;
	add_history(line);
	if (ft_str_startswith(line, "exit"))
		get_prompter()->keep_prompting = false;
	else if (ft_str_startswith(line, "clear"))
	{

		int abc = system("clear");
		(void)abc;
	}
	else if (ft_str_startswith(line, "env"))
		get_envp()->print();
	else
	{
		logger()->debug(\
			"got line: %s at: %s\n", \
			line,
			get_envp()->get_value("PWD")
	)	;
	}
	free(line);
}

static t_prompter	*prompter_create(void)
{
	t_prompter	*prompter;

	prompter = ft_calloc(1, sizeof(t_prompter));
	if (!prompter)
		return (NULL);
	prompter->prompt = prompter_prompt;
	prompter->keep_prompting = true;
	return (prompter);
}

static void	prompter_destroy(t_prompter *prompter)
{
	rl_clear_history();
	free(prompter);
}

t_prompter	*get_prompter(void)
{
	return (
		get_context(\
			CONTEXT_ID_PROMPTER, \
			(t_context_construct_fn)prompter_create, \
			(void (*)(void *))prompter_destroy \
		)
	);
}
