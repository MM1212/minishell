/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:21:49 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/02 19:01:56 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	child_process(t_info *info, int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	info->pid = fork();
	if (info->pid < 0)
		err_msg_exit(ERR_FORK);
	else if (info->pid == 0)
	{
		handle_pipes(info, argc, argv);
		execve(info->arg_path, info->args, envp);
		free_split(info, info->args);
		while (info->envp_paths && info->envp_paths[i])
			free(info->envp_paths[i++]);
		free(info->envp_paths);
		close(info->old_pipe);
		free(info);
		close(0);
		close(1);
		exit (127);
	}
	close(info->old_pipe);
	info->old_pipe = dup(info->pipe[0]);
}

void	mid_pipes(t_info *info)
{
	dup2(info->pipe[1], STDOUT_FILENO);
	dup2(info->old_pipe, STDIN_FILENO);
}

void	dup2_and_close(t_info *info, int argc)
{
	if (info->i == 2 || (info->i == 3 && info->here_doc))
	{
		dup2(info->infile, STDIN_FILENO);
		dup2(info->pipe[1], STDOUT_FILENO);
		close(info->infile);
	}
	else if (info->i == argc - 2)
	{
		dup2(info->outfile, STDOUT_FILENO);
		dup2(info->old_pipe, STDIN_FILENO);
		close(info->outfile);
	}
}

void	handle_pipes(t_info *info, int argc, char **argv)
{
	if (info->i == 2 || (info->i == 3 && info->here_doc))
	{
		if (!info->here_doc)
			info->infile = open(argv[1], O_RDONLY);
		else
			info->infile = info->old_pipe;
		dup2_and_close(info, argc);
	}
	else if (info->i > 2 && info->i < argc - 2)
		mid_pipes(info);
	else if (info->i == argc - 2)
	{
		if (!info->here_doc)
			info->outfile = open(argv[argc - 1], O_TRUNC | \
			O_CREAT | O_RDWR, 0644);
		else
			info->outfile = open(argv[argc - 1], O_APPEND | \
			O_CREAT | O_RDWR, 0644);
		if (info->outfile < 0)
			exit (1);
		dup2_and_close(info, argc);
	}
	shut_pipe(info);
}

void	one_command_doc(t_info *info, int argc, char *argv[], char **envp)
{
	info->i += 1;
	if (!args_prep(info, argv))
		cmd_error(info->args[0]);
	info->pid = fork();
	if (info->pid == 0)
	{
		info->infile = open("tmp.txt", O_RDONLY);
		info->outfile = open(argv[argc - 1], O_APPEND | \
		O_CREAT | O_RDWR, 0644);
		if (info->outfile < 0)
			err_msg_exit(ERR_OUTFILE);
		else if (info->infile < 0)
			err_msg_exit(ERR_INFILE);
		dup2(info->infile, STDIN_FILENO);
		dup2(info->outfile, STDOUT_FILENO);
		close(info->infile);
		close(info->outfile);
		execve(info->arg_path, info->args, envp);
	}
	waitpid(-1, 0, 0);
	free_split(info, info->args);
	final_free(info);
}
