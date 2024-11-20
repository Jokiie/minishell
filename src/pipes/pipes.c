/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/19 01:47:23 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipes(t_pipes *p)
{
	p->p_args = NULL;
	p->num_pipes = 0;
	p->cmd_num = 0;
	p->pipes = NULL;
    p->ret = 0;
    p->last_cmd = FALSE;
    p->cmd_start = 0;
	p->arg_protected = NULL;
}

int	**allocate_pipes(t_pipes *p)
{
	int	i;

	p->pipes = malloc(sizeof(int *) * p->num_pipes);
	i = 0;
	while (i < p->num_pipes)
	{
		p->pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(p->pipes[i]) == -1)
		{
			perror("minishell: pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (p->pipes);
}

void	close_pipes(t_pipes *p)
{
	int	i;

	i = 0;
	while (i < p->num_pipes)
	{
		close(p->pipes[i][0]);
		close(p->pipes[i][1]);
		free(p->pipes[i]);
		i++;
	}
	free(p->pipes);
}

void	pipes_redirection(t_pipes *p)
{
	if (p->cmd_num > 0)
		dup2(p->pipes[p->cmd_num - 1][0], STDIN_FILENO);
	if (p->cmd_num < p->num_pipes)
		dup2(p->pipes[p->cmd_num][1], STDOUT_FILENO);
}
