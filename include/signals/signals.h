/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:09:56 by martiper          #+#    #+#             */
/*   Updated: 2023/06/05 11:02:31 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 700
# endif
# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif
# include <shared.h>

void	signals_hook(void);

#endif
