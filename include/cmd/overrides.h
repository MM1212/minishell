/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overrides.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:19 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 15:46:54 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OVERRIDES_H
# define OVERRIDES_H

int		cmds_overrides_cd_cmd(int ac, char **av);
void	cmds_overrides_cd_cmd_on_execute(int ac, char **av, int exit_code);
int		cmds_overrides_env_cmd(int ac, char **av);
int		cmds_overrides_exit_cmd(int ac, char **av);
void	cmds_overrides_exit_cmd_on_execute(int ac, char **av, int exit_code);
int		cmds_overrides_pwd_cmd(int ac, char **av);
int		cmds_overrides_internal_expand_cmd(int ac, char **av);
int		cmds_overrides_echo_cmd(int ac, char **args);

#endif
