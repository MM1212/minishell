/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 02:27:03 by martiper          #+#    #+#             */
/*   Updated: 2023/06/05 12:03:42 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <log/log.h>
#include <prompter/prompter.h>
#include <context/context.h>
#include <env/registry.h>
#include <cmd/storage.h>
#include <signals/signals.h>
#include <runner/runner.h>
#include <dir/dir.h>

static void	init_ctxs(void)
{
	get_envp();
	get_runner();
	get_cmds();
	get_prompter();
	get_dir();
}

int	main(int ac, char **av, char **env)
{
	t_prompter	*prompter;
	t_envp		*envp;
	t_cmds		*cmds;
	int			exit_code;

	(void)ac;
	(void)av;
	exit_code = 0;
	init_ctxs();
	envp = get_envp();
	prompter = get_prompter();
	cmds = get_cmds();
	if (!prompter || !envp || !cmds)
		return (EXIT_FAILURE);
	if (!envp->init(env) || !cmds->store())
	{
		prompter->keep_prompting = false;
		exit_code = EXIT_FAILURE;
	}
	signals_hook();
	while (prompter->keep_prompting)
		prompter->prompt();
	exit_code = ft_atoi(envp->get_value("?"));
	destroy_all_contexts();
	return (ft_printf("exit\n"), exit_code);
}
