/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:49:14 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 16:54:10 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompter/prompter.h"
#include <context/context.h>
#include <runner/runner.h>
#include <utils/quit.h>

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
		free(line);
		return ;
	}
	if (!prompter_check_if_empty(line))
		return ;
	add_history(line);
	get_runner()->run(line);
	free(line);
}

static void	prompter_skip_current_line(void)
{
	size_t	wrote;

	(void)wrote;
	if (!get_prompter()->prompting)
		return ;
	wrote = write(1, "^C\n", 3);
	rl_replace_line("", 1);
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
