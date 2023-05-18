/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:53:43 by martiper          #+#    #+#             */
/*   Updated: 2023/05/18 13:09:26 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

typedef struct s_env_var
{
	char	*name;
	char	*value;
}	t_env_var;

t_env_var	*env_build_var(char *name, char *value);
t_env_var	env_build_var_from_str(char *entry);
void		env_delete_var(t_env_var *var);
char		*env_var_to_string(t_env_var *var);

#endif
