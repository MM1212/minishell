/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:52:01 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 22:52:08 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include "env/var.h"

char	*env_var_to_string(t_env_var *var)
{
	char	*str;
	size_t	len;

	if (!var)
		return (NULL);
	len = ft_strlen(var->name) + ft_strlen(var->value) + 1;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_sprintf(\
		str, len + 1, \
		"%s=%s", \
		var->name, \
		var->value \
	);
	return (str);
}
