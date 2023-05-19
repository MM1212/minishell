/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:49:14 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:28:51 by martiper         ###   ########.fr       */
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
	// if (ft_str_startswith(line, "exit"))
	// 	get_prompter()->keep_prompting = false;
	// else if (ft_str_startswith(line, "clear"))
	// {
	// 	int abc = system("clear");
	// 	(void)abc;
	// }
	// else if (ft_str_startswith(line, "env"))
	// 	get_envp()->print();
	// else if (ft_str_startswith(line, "cd"))
	// {
	// 	char **args = ft_split(line, " ");
	// 	get_dir()->go_to(args[1]);
	// 	ft_split_free(args);
	// }
	// else if (ft_str_startswith(line, "$"))
	// 	ft_printf("%s\n", get_envp()->get_value(line + 1));
	// else
	{
		char **args = ft_split(line, " ");
		if (args)
		{
			if (get_cmds()->exists(args[0]))
			{
				char *cmd = args[0];
				int ac = 0;
				while ((args + 1)[ac])
					ac++;
				if (get_cmds()->exec(cmd, ac, args + 1) != EXIT_SUCCESS)
					display_error(cmd);
			}
			else
			{
				logger()->debug(\
					"got line: %s at: %s\n", \
					line,
					get_envp()->get_value("PWD")
				);
				char *exec_path = get_envp()->path->find_path(args[0]);
				if (exec_path)
					logger()->debug("Found executable path at: %s\n", exec_path);
				else
					logger()->error("Command %s not found.\n", args[0]);
				free(exec_path);
			}
			ft_split_free(args);
		}
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
