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

int	ft_pipes_int_out(t_minishell *ms, int nbr_pipes, int i, int j)
{
	int		cmd_start;
	int		cmd_end;
	int		cmd_num;
	char	args_count;
	char	**args;

	i = -1;
	cmd_start = 0;
	cmd_num = 0;
	while (++i <= nbr_pipes)
	{
		cmd_end = cmd_start;
		while (ms->tokens[cmd_end] != NULL && ft_strcmp(ms->tokens[cmd_end], "|") != 0)
			cmd_end++;
		args_count = cmd_end - cmd_start;
		args = malloc(sizeof(char *) * (args_count + 1));
		if (!args)
			return (EXIT_FAILURE);
		j = -1;
		while (++j < args_count)
			args[j] = ms->tokens[cmd_start + j];
		args[args_count] = NULL;
	}

}

int	ft_pipes_fork(t_minishell *ms, int cmd_num, int num_pipes, int **pipes)
{
	pid_t	pid;
	int		i;
	int		j;

	i = -1;
	j = 0;
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		if (cmd_num > 0)
		{
			if (dup2(pipes[cmd_num - 1][0], STDIN_FILENO) == -1)
				exit (EXIT_FAILURE);
		}
		if (cmd_num < num_pipes)
		{
			if (dup2(pipes[cmd_num][1], STDOUT_FILENO) == -1)
				exit (EXIT_FAILURE);
		}
		while (++i < num_pipes)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		execvp(args[0], args);
		exit(EXIT_FAILURE);
	}
}
