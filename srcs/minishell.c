/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 02:27:03 by martiper          #+#    #+#             */
/*   Updated: 2023/05/18 13:21:08 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <log/log.h>
#include <prompter/prompter.h>
#include <context/context.h>
#include <env/registry.h>

int	main(int ac, char **av, char **env)
{
	t_prompter	*prompter;
	t_envp		*envp;

	(void)ac;
	(void)av;
	(void)env;
	logger()->info("Minishell starting..\n");
	envp = get_envp();
	prompter = get_prompter();
	if (!prompter || !envp)
		return (EXIT_FAILURE);
	if (!envp->init(env))
		prompter->keep_prompting = false;
	while (prompter->keep_prompting)
		prompter->prompt();
	destroy_all_contexts();
	return (0);
}
