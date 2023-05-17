/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:08:41 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 13:12:19 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log/log_fns.h"

void	log_do_debug(char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	logger_do_log(LOG_DEBUG, fmt, args);
	va_end(args);
}

void	log_do_info(char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	logger_do_log(LOG_INFO, fmt, args);
	va_end(args);
}

void	log_do_warn(char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	logger_do_log(LOG_WARN, fmt, args);
	va_end(args);
}

void	log_do_error(char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	logger_do_log(LOG_ERROR, fmt, args);
	va_end(args);
}
