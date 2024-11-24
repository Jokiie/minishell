/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/24 08:52:32 by ccodere          ###   ########.fr       */
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

	ms->p.pipes = ft_calloc(ms->p.num_pipes, sizeof(int *));
	i = 0;
	while (i < ms->p.num_pipes)
	{
		ms->p.pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(ms->p.pipes[i]) == -1)
		{
			perror("ms: pipe");
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
	if (!ms->p.pipes || !*ms->p.pipes)
		return ;
    while (i < ms->p.num_pipes)
    {
        close(ms->p.pipes[i][0]);
        close(ms->p.pipes[i][1]);
        free(ms->p.pipes[i]);
		ms->p.pipes[i] = NULL;
        i++;
    }
    free(ms->p.pipes);
    ms->p.pipes = NULL;
}

int	pipes_redirection(t_minishell *ms)
{
	if (!ms->p.pipes)
		return (FAIL);
	if (ms->p.cmd_num > 0)
	{
		if (dup2(ms->p.pipes[ms->p.cmd_num - 1][0], STDIN_FILENO) == -1)
		{
			perror("ms: dup2 stdin");
			return (FAIL);
		}
	}
	if (ms->p.cmd_num < ms->p.num_pipes)
	{
		if (dup2(ms->p.pipes[ms->p.cmd_num][1], STDOUT_FILENO) == -1)
		{
			perror("ms: dup2 stdout");
			return (FAIL);
		}
	}
	return (SUCCESS);
}
