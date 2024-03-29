/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:19:21 by martiper          #+#    #+#             */
/*   Updated: 2023/06/02 13:15:51 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env/registry.h>
#include <prompter/prompter.h>
#include <context/context.h>
#include "utils/quit.h"

void	quit(int exit_code)
{
	if (exit_code == -1)
		exit_code = ft_atoi(get_envp()->get_value("?"));
	destroy_all_contexts();
	ft_printf("exit\n");
	exit(exit_code);
}
