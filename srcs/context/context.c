/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:46:13 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 12:46:19 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include "context/context.h"

void	*get_context_destructor(int ctx_id, void (*destroy)(void *))
{
	static void	(*destructors[MAX_CONTEXTS])(void *);

	if (ctx_id < 0 || ctx_id >= MAX_CONTEXTS)
		return (NULL);
	if (!destructors[ctx_id])
		destructors[ctx_id] = destroy;
	return (destructors[ctx_id]);
}

void	*get_context(int ctx_id, void *(*init)(void), void (*destroy)(void *))
{
	static void	*contexts[MAX_CONTEXTS];

	if (ctx_id < 0 || ctx_id >= MAX_CONTEXTS)
		return (NULL);
	if (!contexts[ctx_id])
	{
		contexts[ctx_id] = init();
		(void)get_context_destructor(ctx_id, destroy);
	}
	return (contexts[ctx_id]);
}

void	destroy_context(int ctx_id)
{
	void	*ctx;
	void	(*destroy)(void *);

	if (ctx_id < 0 || ctx_id >= MAX_CONTEXTS)
		return ;
	ctx = get_context(ctx_id, NULL, NULL);
	destroy = (void (*)(void *))get_context_destructor(ctx_id, NULL);
	if (ctx && destroy)
		destroy(ctx);
}

void	destroy_all_contexts(void)
{
	size_t	i;

	i = 0;
	while (i < MAX_CONTEXTS)
		destroy_context(i++);
}
