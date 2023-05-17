/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:45:50 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 12:47:07 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events/events.h"
#include <context/context.h>

bool	event_manager_on(t_sl_event_type type, t_sl_event_callback callback)
{
	t_sl_event_manager	*event_manager;
	t_sl_event			*event;
	t_list				*node;

	event_manager = get_event_manager_ctx();
	event = ft_calloc(1, sizeof(t_sl_event));
	if (!event)
		return (false);
	event->type = type;
	event->callback = callback;
	node = ft_lstnew(event);
	if (!node)
	{
		free(event);
		return (false);
	}
	ft_lstadd_back(&event_manager->events, node);
	return (true);
}

bool	event_manager_emit(t_sl_event_type type, void *data)
{
	t_sl_event_manager	*event_manager;
	t_list				*node;
	t_sl_event			*event;
	bool				emitted;

	emitted = false;
	event_manager = get_event_manager_ctx();
	node = event_manager->events;
	while (node)
	{
		event = (t_sl_event *)node->content;
		if (event->type == type)
		{
			emitted = true;
			event->callback(data);
		}
		node = node->next;
	}
	return (emitted);
}

static void	*event_manager_init(void)
{
	t_sl_event_manager	*event_manager;

	event_manager = ft_calloc(1, sizeof(t_sl_event_manager));
	if (!event_manager)
		return (NULL);
	event_manager->events = NULL;
	event_manager->on = event_manager_on;
	event_manager->emit = event_manager_emit;
	return (event_manager);
}

static void	event_manager_destroy(void *ctx)
{
	t_sl_event_manager	*event_manager;

	event_manager = (t_sl_event_manager *)ctx;
	ft_lstclear(&event_manager->events, free);
	free(event_manager);
}

t_sl_event_manager	*get_event_manager_ctx(void)
{
	return (get_context(\
		CONTEXT_ID_EVENT_MANAGER, \
		event_manager_init, \
		event_manager_destroy \
	));
}
