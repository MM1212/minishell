/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:48:07 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 13:59:58 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPTER_H
# define PROMPTER_H

# include <shared.h>

typedef struct s_prompter
{
	bool	keep_prompting;
	bool	prompting;
	void	(*prompt)(void);
	void	(*skip_current_line)(void);
}	t_prompter;

t_prompter	*get_prompter(void);
void		prompter_get_prefix(char *prefix);

#endif
