/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:45:59 by martiper          #+#    #+#             */
/*   Updated: 2023/05/17 12:46:00 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <shared.h>

typedef enum s_event_type
{
	EVENT_ON_NEW_COMMAND
}					t_sl_event_type;

typedef struct s_event
{
	t_sl_event_type	type;
	void			(*callback)(void *);
}					t_sl_event;

typedef void	(*t_sl_event_callback)(void *);
typedef bool	(*t_sl_event_on)(\
	t_sl_event_type type, \
	t_sl_event_callback callback \
);
typedef bool	(*t_sl_event_emit)(\
	t_sl_event_type type, \
	void *data \
);

typedef struct s_event_manager
{
	t_list			*events;
	t_sl_event_on	on;
	t_sl_event_emit	emit;
}	t_sl_event_manager;

t_sl_event_manager	*get_event_manager_ctx(void);
bool				event_manager_on(\
	t_sl_event_type type, \
	t_sl_event_callback callback \
);
bool				event_manager_emit(t_sl_event_type type, void *data);

#endif
