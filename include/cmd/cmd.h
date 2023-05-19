/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:50:59 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 14:00:56 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef int	(*t_cmd_handler)(int ac, char **av);

typedef struct s_cmd
{
	char			*name;
	t_cmd_handler	handler;
}	t_cmd;

t_cmd	*cmds_create_cmd(char *cmd, t_cmd_handler handler);
void	cmds_clear_cmd(t_cmd *cmd);
#endif
