/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:01:47 by martiper          #+#    #+#             */
/*   Updated: 2023/05/25 20:40:09 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <env/registry.h>

size_t	runner_sanitize_args(char **args)
{
	size_t	idx;
	t_envp	*envp;

	envp = get_envp();
	idx = 1;
	while (args[idx])
		envp->expand_arg(args + idx++);
	return (idx);
}
