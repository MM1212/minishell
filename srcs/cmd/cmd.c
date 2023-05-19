/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:58:38 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:01:09 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include "cmd/cmd.h"

t_cmd	*cmds_create_cmd(char *cmd, t_cmd_handler handler)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->name = ft_strdup(cmd);
	new->handler = handler;
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
