/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:24:10 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 12:35:48 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

/*
	Uses perror to display the error message and returns errno.
	Also puts in the env variable $? the errno.
 */
int	display_error(char *header, char *msg);

#endif
