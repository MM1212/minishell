/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:41:55 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/02 18:05:26 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	ft_fixer_mover(char *buffer, int gate, int i)
{
	int	k;

	k = 0;
	if (gate)
	{
		while (buffer[i])
		{
			buffer[k++] = buffer[i];
			buffer[i++] = 0;
		}
	}
}

int	ft_tidy(char *buffer)
{
	int	gate;
	int	i;

	i = 0;
	gate = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			gate = 1;
			buffer[i++] = 0;
			break ;
		}
		buffer[i++] = 0;
	}
	ft_fixer_mover(buffer, gate, i);
	return (gate);
}

char	*line_join(char *s1, char *s2)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char *)malloc((sizeof(char) * \
	(ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!new_str)
		return (0);
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	while (*s2)
	{
		new_str[i++] = *s2;
		if (*s2++ == '\n')
			break ;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	clean_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		buffer[i++] = '\0';
	exit (0);
}

int	get_line(t_info *info, char *delim)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = 0;
	if (read(0, 0, 0) < 0 || BUFFER_SIZE <= 0)
		clean_buffer(buffer);
	if (*buffer || read(0, buffer, BUFFER_SIZE) > 0)
		line = line_join(line, buffer);
	(ft_tidy(buffer));
	if (!ft_strncmp(delim, line, ft_strlen(delim)) && \
		!ft_strncmp(delim, line, ft_strlen(line) - 1))
	{
		free(line);
		return (0);
	}
	if (!line)
		return (0);
	write(info->pipe[1], line, ft_strlen(line));
	free(line);
	return (1);
}
