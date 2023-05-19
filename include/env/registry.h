/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:11:19 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 12:49:10 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGISTRY_H
# define REGISTRY_H

# include <shared.h>
# include "var.h"
# include "path/path.h"

typedef bool			(*t_env_registry_add_env_fn)(char *name, char *value);

typedef struct s_env_registry
{
	t_list						*vars;
	size_t						(*size)(void);
	t_env_var					*(*get)(char *name);
	char						*(*get_value)(char *name);
	t_env_registry_add_env_fn	add;
	void						(*set)(char *name, char *value);
	bool						(*unset)(char *name);
	char						**(*get_env)(void);
	bool						(*is_set)(char *name);
	void						(*print)(void);
	bool						(*init)(char **envp);
	t_env_path					*path;
}						t_env_registry;

typedef t_env_registry	t_envp;

t_env_registry	*get_envp(void);

#endif
