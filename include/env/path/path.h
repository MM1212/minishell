/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:42:07 by martiper          #+#    #+#             */
/*   Updated: 2023/05/19 13:25:27 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <shared.h>

typedef struct s_env_path
{
	char	*(*get)(void);
	char	**(*get_paths)(void);
	char	*(*find_path)(char *exec);
}	t_env_path;

#endif
