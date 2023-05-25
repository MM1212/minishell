/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:47:38 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 13:56:07 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STORAGE_H
# define STORAGE_H

# include <shared.h>
# include "cmd.h"

typedef bool			(*t_cmd_storage_int_add)(\
	char *cmd, \
	t_cmd_handler handler, \
	t_cmd_on_execute execute \
);

typedef struct s_cmd_storage
{
	t_list					*cmds;
	t_cmd_storage_int_add	add;
	bool					(*remove)(char *cmd);
	bool					(*exists)(char *cmd);
	int						(*exec)(char *cmd, int ac, char **av);
	t_cmd					*(*get)(char *cmd);
	bool					(*store)(void);
}						t_cmd_storage;

typedef t_cmd_storage	t_cmds;

t_cmds	*get_cmds(void);

#endif
