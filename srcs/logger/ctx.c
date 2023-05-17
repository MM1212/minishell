/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:12:22 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 13:31:13 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log/log.h"
#include "log/log_fns.h"
#include <context/context.h>

static t_logger	*logger_create(void)
{
	t_logger	*log;

	log = ft_calloc(1, sizeof(t_logger));
	if (!log)
		return (NULL);
	log->debug = log_do_debug;
	log->info = log_do_info;
	log->warn = log_do_warn;
	log->error = log_do_error;
	return (log);
}

t_logger	*logger(void)
{
	return (get_context(\
		CONTEXT_ID_LOGGER, \
		(void *(*)(void))logger_create, \
		free \
	));
}
