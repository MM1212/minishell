/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:37 by martiper          #+#    #+#             */
/*   Updated: 2023/05/24 16:43:48 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"
#include <dir/dir.h>
#include <errno.h>

int	cmds_overrides_pwd_cmd(int ac, char **av)
{
	char	*path;

	(void)ac;
	(void)av;
	path = get_dir()->get_full();
	ft_printf("%s\n", path);
	free(path);
	return (0);
}
