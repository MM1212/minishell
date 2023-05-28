/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overrides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:10:15 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 23:18:20 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/storage.h"
#include "cmd/cmd_fns.h"
#include "cmd/overrides.h"

static int	no_op(int ac, char **av)
{
	(void)ac;
	(void)av;
	return (0);
}

bool	cmds_register_cmds(void)
{
	t_cmds	*cmds;

	cmds = get_cmds();
	if (!cmds)
		return (false);
	if (!cmds->add("cd", no_op, cmds_overrides_cd_cmd))
		return (false);
	if (!cmds->add("env", cmds_overrides_env_cmd, NULL))
		return (false);
	if (!cmds->add("exit", \
		no_op, cmds_overrides_exit_cmd))
		return (false);
	if (!cmds->add("pwd", cmds_overrides_pwd_cmd, NULL))
		return (false);
	if (!cmds->add("echo", cmds_overrides_echo_cmd, NULL))
		return (false);
	if (!cmds->add("export", cmds_overrides_export_show_available_vars, \
		cmds_overrides_export_cmd))
		return (false);
	if (!cmds->add("unset", no_op, cmds_overrides_unset_cmd))
		return (false);
	return (true);
}
