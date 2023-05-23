/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:44:04 by martiper          #+#    #+#             */
/*   Updated: 2023/05/23 13:15:28 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# define MAX_CONTEXTS 16

typedef enum e_context_ids
{
	CONTEXT_ID_EVENT_MANAGER,
	CONTEXT_ID_LOGGER,
	CONTEXT_ID_RUNNER,
	CONTEXT_ID_CMD_STORAGE,
	CONTEXT_ID_PROMPTER,
	CONTEXT_ID_DIRECTORY_MANAGER,
	CONTEXT_ID_ENV_REGISTRY
}	t_context_ids;

typedef void	*(*t_context_construct_fn)(void);
typedef void	(*t_context_destruct_fn)(void *);

void	*get_context(int ctx_id, void *(*init)(void), void (*destroy)(void *));
void	*get_context_destructor(int ctx_id, void (*destroy)(void *));
void	destroy_context(int ctx_id);
void	destroy_all_contexts(void);

#endif
