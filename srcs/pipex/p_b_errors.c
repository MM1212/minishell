/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:28:35 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 20:59:35 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	custm_err_msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

void	err_msg_exit(char *error)
{
	perror(error);
	exit(1);
}

void	cmd_error(char *cmd)
{
	char	*temp1;
	char	*temp2;

	if (cmd[0] == '/')
		temp1 = ft_strjoin(ERR_CMD2, cmd);
	else
		temp1 = ft_strjoin(ERR_CMD1, cmd);
	temp2 = ft_strjoin(temp1, "\n");
	write(2, temp2, ft_strlen(temp2));
	free(temp1);
	free(temp2);
	exit(1);
}
