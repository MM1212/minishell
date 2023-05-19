/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:02:43 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 21:46:45 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	args_prep(t_info *info, char **argv)
{
	int	j;

	if (info->i == 2 && info->here_doc)
		info->i += 1;
	info->args = ft_split(argv[info->i], ' ');
	j = -1;
	while (info->envp_paths[++j])
		if (path_check(info, j))
			return ;
	info->arg_path = 0;
}

int	path_check(t_info *data, int j)
{
	char	*temp1;
	char	*temp2;

	if (check_char(data))
		return (sort_arg(data));
	temp1 = ft_strjoin(data->envp_paths[j], "/");
	temp2 = ft_strjoin(temp1, data->args[0]);
	if (access(temp2, F_OK) == 0)
	{
		data->arg_path = strdup(temp2);
		free(temp1);
		free(temp2);
		return (1);
	}
	free(temp1);
	free(temp2);
	return (0);
}

int	check_char(t_info *info)
{
	int		j;

	j = -1;
	while (info->args[0] && info->args[0][++j])
	{
		if (info->args[0][j] == '/')
			return (1);
	}
	return (0);
}

int	sort_arg(t_info *info)
{
	char	*temp;

	if (info->args[0][0] == '/' || info->args[0][0] == '.')
	{
		if (access(info->args[0], F_OK) == 0)
		{
			info->arg_path = strdup(info->args[0]);
			return (1);
		}
	}
	else
	{
		temp = ft_strjoin("./", info->args[0]);
		info->arg_path = ft_strdup(temp);
		free(temp);
		return (1);
	}
	return (0);
}
