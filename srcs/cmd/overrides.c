/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overrides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:10:15 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 15:44:57 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/storage.h"
#include "cmd/cmd_fns.h"
#include "cmd/overrides.h"

bool	cmds_register_cmds(void)
{
	t_cmds	*cmds;

	cmds = get_cmds();
	if (!cmds)
		return (false);
	if (!cmds->add("cd", cmds_overrides_cd_cmd, cmds_overrides_cd_cmd_on_execute))
		return (false);
	if (!cmds->add("env", cmds_overrides_env_cmd, NULL))
		return (false);
	if (!cmds->add("exit", cmds_overrides_exit_cmd, cmds_overrides_exit_cmd_on_execute))
		return (false);
	if (!cmds->add("pwd", cmds_overrides_pwd_cmd, NULL))
		return (false);
	if (!cmds->add("int_expand", cmds_overrides_internal_expand_cmd, NULL))
		return (false);
	if (!cmds->add("echo", cmds_overrides_echo_cmd, NULL))
		return (false);
	return (true);
}
