/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:27:00 by martiper          #+#    #+#             */
/*   Updated: 2023/06/05 11:27:18 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signals.h"
#include <prompter/prompter.h>

static void	no_op(int sig)
{
	(void)sig;
}

static void	sigint_handler(int sig)
{
	(void)sig;
	get_prompter()->skip_current_line();
}

void	sigchld_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)ctx;
	if (!info)
		return ;
	if (info->si_code == CLD_DUMPED)
		ft_printf("Quit (core dumped)\n");
}

void	signals_hook(void)
{
	struct sigaction	sigact;

	sigact.sa_sigaction = sigchld_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGCHLD, &sigact, NULL);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, no_op);
	signal(SIGTSTP, no_op);
}
