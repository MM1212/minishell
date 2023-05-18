/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:48:07 by martiper          #+#    #+#             */
/*   Updated: 2023/05/18 11:00:19 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPTER_H
# define PROMPTER_H

# include <shared.h>

typedef struct s_prompter
{
	bool	keep_prompting;
	void	(*prompt)(void);
}	t_prompter;

t_prompter	*get_prompter(void);

#endif
