/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:54:46 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 16:51:23 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/storage.h"
#include "cmd/cmd_fns.h"
#include <context/context.h>

static t_cmds	*cmd_storage_create(void)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->cmds = NULL;
	cmds->add = cmds_add_cmd;
	cmds->remove = cmds_remove_cmd;
	cmds->exists = cmds_cmd_exists;
	cmds->exec = cmds_exec_cmd;
	cmds->get = cmds_get_cmd;
	cmds->store = cmds_register_cmds;
	return (cmds);
}

static void	cmd_storage_destroy(t_cmds *cmds)
{
	if (!cmds)
		return ;
	ft_lstclear(&cmds->cmds, (void (*)(void *))cmds_clear_cmd);
	free(cmds);
}

t_cmds	*get_cmds(void)
{
	return (
		get_context(\
			CONTEXT_ID_CMD_STORAGE, \
			(void *(*)(void))cmd_storage_create, \
			(void (*)(void *))cmd_storage_destroy \
		)
	);
}
