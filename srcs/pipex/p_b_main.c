/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:37 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/02 19:01:18 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	shut_pipe(t_info *info)
{
	close(info->pipe[0]);
	close(info->pipe[1]);
}

void	final_free(t_info *info)
{
	int	i;

	i = 0;
	while (info->i > 2)
	{
		waitpid(-1, 0, 0);
		info->i--;
	}
	close(info->old_pipe);
	close (info->outfile);
	close (info->infile);
	while (info->envp_paths && info->envp_paths[i])
		free(info->envp_paths[i++]);
	free(info->envp_paths);
	free(info);
	unlink("tmp.txt");
	exit (0);
}

void	get_paths(t_info *data, char **envp)
{
	int	j;

	j = -1;
	while (envp && envp[++j])
	{
		if (ft_strncmp(envp[j], "PATH=", 5) == 0)
		{
			data->envp_paths = ft_split(&envp[j][5], ':');
			return ;
		}
	}
	return ;
}

void	here_doc(t_info *info, char *argv[])
{
	if (pipe(info->pipe) < 0)
		err_msg_exit(ERR_PIPE);
	while (1)
		if (!(get_line(info, argv[2])))
			break ;
	info->old_pipe = dup(info->pipe[0]);
	shut_pipe(info);
	info->here_doc = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	if (argc < 5)
		return (custm_err_msg(ERR_INPUT));
	info = ft_calloc(1, sizeof(t_info));
	info->i = 1;
	get_paths(info, envp);
	if (ft_strlen(argv[1]) == ft_strlen("here_doc") && \
		!(ft_strncmp("here_doc", argv[1], 8)))
		here_doc(info, argv);
	check_file_error(info, argc, argv);
	if ((argc == 5 && info->here_doc))
		one_command_doc(info, argc, argv, envp);
	while ((++(info->i) <= argc - 2))
	{
		if (pipe(info->pipe) < 0)
			err_msg_exit(ERR_PIPE);
		if (!args_prep(info, argv))
			cmd_error(info->args[0]);
		child_process(info, argc, argv, envp);
		shut_pipe(info);
		free_split(info, info->args);
	}
	final_free(info);
}
