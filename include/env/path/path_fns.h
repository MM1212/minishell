/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:47:10 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 12:51:05 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_FNS_H
# define PATH_FNS_H

# include "path.h"

char		**env_path_get_paths(void);
char		*env_path_find_path(char *exec);
t_env_path	*env_path_create(void);

#endif
