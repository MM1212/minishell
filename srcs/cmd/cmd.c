/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:58:38 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 15:10:12 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include "cmd/cmd.h"

t_cmd	*cmds_create_cmd(char *cmd, t_cmd_handler handler, void (*on_execute)(int exit_code))
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->name = ft_strdup(cmd);
	new->handler = handler;
	new->on_execute = on_execute;
	return (new);
}

void	cmds_clear_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->name)
		free(cmd->name);
	free(cmd);
}
