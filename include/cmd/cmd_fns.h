/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fns.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:52:19 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 15:02:01 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_FNS_H
# define CMD_FNS_H

# include "cmd.h"
# include <shared.h>

bool	cmds_add_cmd(char *cmd, t_cmd_handler handler, void (*on_execute)(int exit_code));
bool	cmds_remove_cmd(char *cmd);
bool	cmds_cmd_exists(char *cmd);
int		cmds_exec_cmd(char *cmd, int ac, char **av);
t_cmd	*cmds_get_cmd(char *cmd);
bool	cmds_register_cmds(void);

#endif
