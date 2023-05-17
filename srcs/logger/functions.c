/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:58:18 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 13:33:47 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log/log_fns.h"
#include "../../libs/libft/src/printf/ft_printf_internal.h"

void	logger_do_log(char *tag, char *fmt, va_list args)
{
	size_t	idx;

	if (!tag || !fmt)
		return ;
	idx = 0;
	ft_printf("%s", tag);
	while (fmt[idx])
	{
		if (fmt[idx] != '%')
		{
			ft_putchar_fd(fmt[idx++], 1);
			continue ;
		}
		ft_putstr_fd("\033[93m", 1);
		ft_def_printf_format(\
			fmt[++idx], args, ft_def_printf_flags(fmt, &idx));
		ft_putstr_fd("\033[39m", 1);
		idx++;
	}
	return ;
}
