/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:47:28 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 13:31:09 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# include <shared.h>

typedef void	(*t_log_fn)(char *fmt, ...);

typedef struct s_logger
{
	t_log_fn	debug;
	t_log_fn	info;
	t_log_fn	warn;
	t_log_fn	error;
}	t_logger;

t_logger	*logger(void);

#endif
