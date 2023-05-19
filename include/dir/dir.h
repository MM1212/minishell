/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:42:12 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 11:09:37 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIR_H
# define DIR_H

# include <env/registry.h>
# include <shared.h>

typedef struct s_dir
{
	char	*(*get_relative)(char *buffer, size_t size);
	char	*(*get_full)(void);
	char	*(*get_home)(void);
	bool	(*is_dir)(char *path);
	bool	(*is_file)(char *path);
	bool	(*is_executable)(char *path);
	bool	(*go_to)(char *path);
}	t_dir;

t_dir	*get_dir(void);

#endif
