/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry_fns.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:27:06 by martiper          #+#    #+#             */
/*   Updated: 2023/05/18 13:30:24 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGISTRY_FNS_H
# define REGISTRY_FNS_H

# include "var.h"

t_env_var	*env_registry_get_var(char *name);
char		*env_registry_get_var_value(char *name);
bool		env_registry_add_var(char *name, char *value);
void		env_registry_set_var(char *name, char *value);
bool		env_registry_unset_var(char *name);
bool		env_registry_is_var_set(char *name);
bool		env_registry_init(char **envp);
char		**env_registry_get_env(void);
void		env_registry_print(void);

#endif
