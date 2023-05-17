/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:44:04 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 13:14:53 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# define MAX_CONTEXTS 16

typedef enum e_context_ids
{
	CONTEXT_ID_EVENT_MANAGER,
	CONTEXT_ID_LOGGER,
}	t_context_ids;

void	*get_context(int ctx_id, void *(*init)(void), void (*destroy)(void *));
void	*get_context_destructor(int ctx_id, void (*destroy)(void *));
void	destroy_context(int ctx_id);
void	destroy_all_contexts(void);

#endif
