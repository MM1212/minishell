/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:23:23 by martiper          #+#    #+#             */
/*   Updated: 2023/05/20 12:24:36 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_H
# define QUIT_H

/*
**	Quit the program with the given exit code.
**
**	@param exit_code The exit code. If `-1` is given,
**the exit code will be the value of the $? env variable.
 */
void	quit(int exit_code);

#endif
