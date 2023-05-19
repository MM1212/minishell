/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:22:54 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:41:04 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/error.h"
#include <env/registry.h>

int	display_error(char *msg)
{
	t_envp	*envp;
	char	*err_code;
	char	err_msg[1024];

	envp = get_envp();
	if (!envp)
		return (1);
	ft_sprintf(err_msg, 1024, "minishell: %s", msg);
	perror(err_msg);
	err_code = ft_itoa(errno);
	envp->set("?", err_code);
	free(err_code);
	return (errno);
}
