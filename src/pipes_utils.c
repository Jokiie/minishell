/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:56:08 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/18 15:56:29 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_minishell *ms, char **str)
{
	int	i;
	int	num_pipes;

	i = 0;
	num_pipes = 0;
	while (str[i])
	{
		if (ms->token.protected[i] == 0 && is_pipe(str[i]))
			num_pipes++;
		i++;
	}
	return (num_pipes);
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

char	**extract_args(char **tokens, int start, int end)
{
	int		i;
	int		size;
	char	**args;

	size = end - start;
	args = ft_calloc(size + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < size)
	{
		args[i] = tokens[start + i];
		i++;
	}
	args[size] = NULL;
	return (args);
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