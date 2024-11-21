/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/21 03:02:06 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exec_pipes(t_minishell *ms, int *i)
{
	init_pipes(ms);
	*i = 0;
	ms->p.cmd_start = *i;
	ms->p.num_pipes = count_type(ms->tokens, &ms->token.protected, is_pipe);
	if (ms->p.num_pipes > 0)
    	ms->p.pipes = allocate_pipes(ms);
}

void	init_pipes(t_minishell *ms)
{
	ms->p.p_args = NULL;
	ms->p.num_pipes = 0;
	ms->p.cmd_num = 0;
	ms->p.pipes = NULL;
	ms->p.ret = 0;
	ms->p.last_cmd = FALSE;
	ms->p.cmd_start = 0;
	ms->p.arg_protected = NULL;
}

int	**allocate_pipes(t_minishell *ms)
{
	int	i;

	ms->p.pipes = malloc(sizeof(int *) * ms->p.num_pipes);
	i = 0;
	while (i < ms->p.num_pipes)
	{
		ms->p.pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(ms->p.pipes[i]) == -1)
		{
			perror("minishell: pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (ms->p.pipes);
}

void	close_pipes(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < ms->p.num_pipes)
	{
		close(ms->p.pipes[i][0]);
		close(ms->p.pipes[i][1]);
		free(ms->p.pipes[i]);
		i++;
	}
	free(ms->p.pipes);
}

int	pipes_redirection(t_minishell *ms)
{
	if (ms->p.cmd_num > 0)
	{
		if (dup2(ms->p.pipes[ms->p.cmd_num - 1][0], STDIN_FILENO) == -1)
		{
			ft_fprintf(2, "ms: dup2 stdin error: %s\n", strerror(errno));
			return (FAIL);
		}
	}
	if (ms->p.cmd_num < ms->p.num_pipes)
	{
		if (dup2(ms->p.pipes[ms->p.cmd_num][1], STDOUT_FILENO) == -1)
		{
			ft_fprintf(2, "ms: dup2 stdout error: %s\n", strerror(errno));
			return (FAIL);
		}
	}
	return (SUCCESS);
}
