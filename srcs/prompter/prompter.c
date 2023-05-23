/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:49:14 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 14:34:33 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompter/prompter.h"
#include <context/context.h>
#include <utils/colors.h>
#include <log/log.h>
#include <env/registry.h>
#include <dir/dir.h>
#include <cmd/storage.h>
#include <utils/error.h>
#include <utils/quit.h>
#include <runner/runner.h>

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
	get_prompter()->prompting = true;
	line = readline(prefix);
	get_prompter()->prompting = false;
	if (!line || line[0] == '\n' || line[0] == '\0')
	{
		if (!line)
			quit(0);
		return ;
	}
	add_history(line);
	{
		get_runner()->run(line);
	}
	free(line);
}

static void prompter_skip_current_line(void)
{
	size_t	wrote;

	(void)wrote;
	wrote = write(1, "^C", 2);
	rl_replace_line("", 1);
	wrote = write(0, "\r\n", 2);
	rl_on_new_line();
	rl_redisplay();
}

static t_prompter	*prompter_create(void)
{
	t_prompter	*prompter;

	prompter = ft_calloc(1, sizeof(t_prompter));
	if (!prompter)
		return (NULL);
	prompter->keep_prompting = true;
	prompter->prompt = prompter_prompt;
	prompter->skip_current_line = prompter_skip_current_line;
	rl_catch_signals = 0;
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
