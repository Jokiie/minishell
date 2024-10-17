// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipes.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
// /*   Updated: 2024/10/09 16:15:45 by matislessar      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/minishell.h"

/*Recreate tokens for the pipes characters*/

// void	ft_pipe_token(t_minishell *ms, int	i)
// {
// 	int	k;
// 	char	**new_tokens;
	
// 	k = 0;
// 	new_tokens = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (new_tokens)
// 		exit(-1);
// 	while (i > k)
// 	{
// 		if (ft_strncmp(ms->tokens[k], "|", 1) != 0)
// 			new_tokens[k] = ms->tokens[k];
// 		k++;
// 	}
// 	new_tokens[k] = NULL;
// 	ms->tokens = new_tokens;
// }

/*Redirection token for pipes*/

void	ft_exec_pipes_redirection(t_minishell *ms)
{
	int	k;

	k = 0;
	while (ms->tokens[k])
	{
		if (ft_strncmp(ms->tokens[k], "|", 1) == 0)
		{
			break ;
		}
		k++;
	}
}

/*Check for pipes*/

int	ft_has_pipe(char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			if (str[i] == '|')
			{
				printf("good/n");
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}

int	ft_exect_pipes(t_minishell *ms)
{
	int		**pipes;
	int		i;
	int		nbr_pipes;

	if (ft_has_pipes(ms->tokens))
	{
		i = -1;
		while (ms->tokens[++i])
		{
			if (ft_strncmp(ms->tokens[i], "|", 1) == 0)
				nbr_pipes++;
		}
		pipes = (int *)malloc(sizeof(int *) * nbr_pipes);
		if (!pipes)
			return (EXIT_FAILURE);
		i = -1;
		while (++i < nbr_pipes)
		{
			pipes[i] = (int)malloc(sizeof(int) * 2);
			if (!pipes[i] || pipe(pipes[i]) == -1)
				return (EXIT_FAILURE);
		}
	}
	return (nbr_pipes);
}

void	ft_pipes_int_out(t_minishell *ms, int nbr_pipes)
{
	int		cmd_start;
	int		cmd_end;
	int		cmd_num;
	int		i;

	i = -1;
	while (++i <= nbr_pipes)
	{
		cmd_end = cmd_start;
		while (ms->tokens[cmd_end] != NULL && ft_strcmp(ms->tokens[cmd_end], "|") != 0)
			cmd_end++;
	}

}

void	ft_pipes(t_minishell *ms)
{

}