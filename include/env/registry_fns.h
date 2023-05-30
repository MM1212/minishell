/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry_fns.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:27:06 by martiper          #+#    #+#             */
/*   Updated: 2023/05/30 11:46:09 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGISTRY_FNS_H
# define REGISTRY_FNS_H

# include "var.h"

typedef enum e_env_var_expansion_state
{
	ENV_VAR_EXPANSION_STATE_NULL,
	ENV_VAR_EXPANSION_STATE_NONE,
	ENV_VAR_EXPANSION_STATE_SINGLE_QUOTE,
	ENV_VAR_EXPANSION_STATE_DOUBLE_QUOTE,
}	t_env_var_expansion_state;

t_env_var	*env_registry_get_var(char *name);
char		*env_registry_get_var_value(char *name);
bool		env_registry_add_var(char *name, char *value);
void		env_registry_set_var(char *name, char *value);
bool		env_registry_unset_var(char *name);
bool		env_registry_is_var_set(char *name);
bool		env_registry_init(char **envp);
char		**env_registry_get_env(void);
void		env_registry_print(void);
void		env_registry_expand_arg(char **arg);
/*
	Ignores quotes and expands everything
 */
void		env_registry_raw_expand_arg(char **arg);
bool		env_registry_is_var_char_valid(char c);
void		env_registry_remove_quotes(char **str);

#endif
