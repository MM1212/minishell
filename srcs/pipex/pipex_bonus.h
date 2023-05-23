/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:22:54 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/02 18:05:37 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_INPUT "invalid number of arguments.\n"
# define ERR_PATHS "couldn't find paths.\n"
# define ERR_PIPE "pipe"
# define ERR_FORK "fork failed"
# define ERR_CMD1 "command not found: "
# define ERR_CMD2 "no such file or directory: "

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_data
{
	char	**envp_paths;
	char	**args;
	char	*arg_path;
	int		pipe[2];
	int		old_pipe;
	int		i;
	int		pid;
	int		infile;
	int		outfile;
	int		here_doc;
}			t_info;

void	cmd_error(char *cmd);
int		sort_arg(t_info *info);
int		sort_arg(t_info *info);
void	shut_pipe(t_info *info);
int		check_char(t_info *info);
int		check_char(t_info *info);
void	final_free(t_info *info);
void	err_msg_exit(char *error);
int		custm_err_msg(char *error);
int		path_check(t_info *data, int j);
int		get_line(t_info *info, char *delim);
int		args_prep(t_info *info, char **argv);
void	free_split(t_info *info, char **strings);
void	handle_pipes(t_info *info, int argc, char **argv);
void	check_file_error(t_info *info, int argc, char *argv[]);
void	child_process(t_info *info, int argc, char **argv, char **envp);
void	one_command_doc(t_info *info, int argc, char *argv[], char **envp);

#endif