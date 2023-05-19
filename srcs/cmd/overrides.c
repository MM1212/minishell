/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overrides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:10:15 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:54:34 by martiper         ###   ########.fr       */
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
	if (!cmds->add("cd", cmds_overrides_cd_cmd))
		return (false);
	if (!cmds->add("env", cmds_overrides_env_cmd))
		return (false);
	if (!cmds->add("exit", cmds_overrides_exit_cmd))
		return (false);
	if (!cmds->add("pwd", cmds_overrides_pwd_cmd))
		return (false);
	return (true);
}
