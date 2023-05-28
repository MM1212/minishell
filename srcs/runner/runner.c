/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martiper <martiper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:07:32 by martiper          #+#    #+#             */
/*   Updated: 2023/05/28 16:49:36 by martiper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner/runner.h"
#include <context/context.h>
#include <utils/quit.h>
#include <env/registry.h>
#include <cmd/storage.h>
#include <env/path/path.h>
#include <utils/error.h>

static bool	runner_prep(\
	char *str, \
	t_runner *runner, \
	t_parser_simple_cmds **init_cmds, \
	size_t *count \
)
{
	*init_cmds = parser((char *)str);
	if (!*init_cmds)
		return (false);
	*count = runner_count_cmds(*init_cmds);
	if (!*count)
		return (false);
	runner->cmds = ft_calloc(*count + 1, sizeof(t_runner_cmd *));
	if (!runner->cmds)
		return (false);
	runner->running = true;
	runner_init_cmds(*init_cmds, runner->cmds, *count);
	return (true);
}

static void	runner_run(const char *str)
{
	t_runner				*runner;
	t_parser_simple_cmds	*init_cmds;
	size_t					count;
	char					**envp;
	size_t					idx;

	runner = get_runner();
	if (!runner)
		return ;
	count = 0;
	if (!runner_prep((char *)str, runner, &init_cmds, &count))
		return ;
	idx = 0;
	envp = get_envp()->get_env();
	while (runner->cmds[idx])
	{
		runner->c_cmd = runner->cmds[idx];
		runner->c_cmd->deps.envp = envp;
		runner_per_cmd(runner, (size_t[2]){idx, count}, init_cmds, envp);
		idx++;
	}
	runner_handle_exit_codes(runner->cmds);
	runner_cleanup();
	parser_clear_cmds(init_cmds);
	ft_split_free(envp);
}

static t_runner	*runner_create(void)
{
	t_runner	*runner;

	runner = ft_calloc(1, sizeof(t_runner));
	if (!runner)
		return (NULL);
	runner->run = runner_run;
	runner->cleanup = runner_cleanup;
	return (runner);
}

static void	runner_destroy(t_runner *runner)
{
	if (!runner)
		return ;
	runner_cleanup();
	free(runner);
}

t_runner	*get_runner(void)
{
	return (
		get_context(\
			CONTEXT_ID_RUNNER, \
			(t_context_construct_fn)runner_create, \
			(t_context_destruct_fn)runner_destroy \
		)
	);
}
