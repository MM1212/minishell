/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:27:00 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 17:12:09 by martiper         ###   ########.fr       */
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

void	signals_hook(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, no_op);
	signal(SIGTSTP, no_op);
}
