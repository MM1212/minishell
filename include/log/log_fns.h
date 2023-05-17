/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_fns.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:53:15 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 13:34:42 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_FNS_H
# define LOG_FNS_H

# include <stdarg.h>

# define LOG_DEBUG "[\033[96mDEBUG\033[39m] "
# define LOG_INFO "[\033[94mINFO\033[39m] "
# define LOG_WARN "[\033[33mWARN\033[39m] "
# define LOG_ERROR "[\033[91mERROR\033[39m] "
# define LOG_SUCCESS "[\033[92mSUCCESS\033[39m] "

void	logger_do_log(char *tag, char *fmt, va_list args);
void	log_do_debug(char *fmt, ...);
void	log_do_info(char *fmt, ...);
void	log_do_warn(char *fmt, ...);
void	log_do_error(char *fmt, ...);
#endif
