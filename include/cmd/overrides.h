/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overrides.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:11:19 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 23:18:20 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OVERRIDES_H
# define OVERRIDES_H

void	cmds_overrides_cd_cmd(int ac, char **av, int *exit_code);
int		cmds_overrides_env_cmd(int ac, char **av);
void	cmds_overrides_exit_cmd(int ac, char **av, int *exit_code);
int		cmds_overrides_pwd_cmd(int ac, char **av);
int		cmds_overrides_echo_cmd(int ac, char **args);
void	cmds_overrides_export_cmd(int ac, char **av, int *exit_code);
int		cmds_overrides_export_show_available_vars(int ac, char **av);
void	cmds_overrides_unset_cmd(int ac, char **av, int *exit_code);

#endif
