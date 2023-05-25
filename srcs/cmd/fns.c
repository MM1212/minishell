/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:57:32 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 13:56:45 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/cmd_fns.h"
#include "cmd/storage.h"

bool	cmds_add_cmd(\
	char *cmd, \
	t_cmd_handler handler, \
	t_cmd_on_execute on_execute \
)
{
	t_cmds	*cmds;
	t_cmd	*new;
	t_list	*node;

	cmds = get_cmds();
	if (!cmds || !cmd || !handler)
		return (false);
	if (cmds->exists(cmd))
		return (false);
	new = cmds_create_cmd(cmd, handler, on_execute);
	if (!new)
		return (false);
	node = ft_lstnew(new);
	if (!node)
	{
		cmds_clear_cmd(new);
		return (false);
	}
	ft_lstadd_back(&cmds->cmds, node);
	return (true);
}

bool	cmds_remove_cmd(char *cmd)
{
	t_cmds	*cmds;
	t_list	*node;
	t_cmd	*cmd_data;

	cmds = get_cmds();
	if (!cmds || !cmd)
		return (false);
	node = cmds->cmds;
	while (node)
	{
		cmd_data = node->content;
		if (!ft_strcmp(cmd_data->name, cmd))
		{
			ft_lstremove(&cmds->cmds, node, (void (*)(void *))cmds_clear_cmd);
			return (true);
		}
		node = node->next;
	}
	return (false);
}

bool	cmds_cmd_exists(char *cmd)
{
	t_cmds	*cmds;
	t_list	*node;
	t_cmd	*cmd_data;

	cmds = get_cmds();
	if (!cmds || !cmd)
		return (false);
	node = cmds->cmds;
	while (node)
	{
		cmd_data = node->content;
		if (!ft_strcmp(cmd_data->name, cmd))
			return (true);
		node = node->next;
	}
	return (false);
}

t_cmd	*cmds_get_cmd(char *cmd)
{
	t_cmds	*cmds;
	t_list	*node;
	t_cmd	*cmd_data;

	cmds = get_cmds();
	if (!cmds || !cmd)
		return (NULL);
	node = cmds->cmds;
	while (node)
	{
		cmd_data = node->content;
		if (!ft_strcmp(cmd_data->name, cmd))
			return (cmd_data);
		node = node->next;
	}
	return (NULL);
}

int	cmds_exec_cmd(char *name, int ac, char **av)
{
	t_cmds	*cmds;
	t_cmd	*cmd;

	cmds = get_cmds();
	if (!cmds || !name)
		return (1);
	cmd = cmds->get(name);
	if (!cmd)
		return (1);
	return (cmd->handler(ac, av));
}
