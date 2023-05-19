/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:22:54 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 11:30:30 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/error.h"
#include <env/registry.h>

int	display_error(char *msg)
{
	t_envp	*envp;
	char	*err_code;

	envp = get_envp();
	if (!envp)
		return (1);
	perror(msg);
	err_code = ft_itoa(errno);
	envp->set("?", err_code);
	free(err_code);
	return (errno);
}
