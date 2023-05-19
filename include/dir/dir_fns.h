/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_fns.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:45:05 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 11:08:51 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIR_FNS_H
# define DIR_FNS_H

# include "dir/dir.h"

char	*dir_get_relative_path(char *buffer, size_t size);
char	*dir_get_full_path(void);
char	*dir_get_home_path(void);
bool	dir_is_path_a_dir(char *path);
bool	dir_is_path_a_file(char *path);
bool	dir_is_path_an_executable(char *path);
bool	dir_go_to_path(char *path);

#endif
