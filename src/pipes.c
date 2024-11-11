/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/10 22:03:02 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_has_pipe(t_minishell *ms, char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			if (ms->token.protected[i] == 0 && ft_strcmp(str[i], "|") == 0)
			{
				ft_fprintf(2, "pipes detect\n");
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}

int	ft_count_pipes(t_minishell *ms, char **str)
{
	int	i;
	int	num_pipes;

	i = 0;
	num_pipes = 0;
	while (str[i])
	{
		if (ms->token.protected[i] == 0 && ft_strcmp(str[i], "|") == 0)
			num_pipes++;
		i++;
	}
	return (num_pipes);
}

int	**ft_allocate_pipes(int num_pipes)
{
	int	i;
	int	**pipes;

	pipes = malloc(sizeof(int *) * num_pipes);
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

char	**ft_extract_args(char **tokens, int start, int end)
{
	int		i;
	int		size;
	char	**args;

	size = end - start;
	// args = malloc(sizeof(char *) * (size + 1));
	args = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		args[i] = tokens[start + i];
		i++;
	}
	args[size] = NULL;
	return (args);
}

void	ft_close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	ft_pipes_redirection(int **pipes, int cmd_num, int num_pipes)
{
	if (cmd_num > 0)
		dup2(pipes[cmd_num - 1][0], STDIN_FILENO);
	if (cmd_num < num_pipes)
		dup2(pipes[cmd_num][1], STDOUT_FILENO);
}

// static int	path(char **envp, t_minishell *ms)
// {
// 	pid_t	pid;
	
// 	while(ft_strncmp(envp, "PATH=", 5))
// 		envp++;
// 	ms->env = *envp;
// 	return (envp);
// }

void	ft_handle_child_process(char **args, int **pipes, int cmd_num, int num_pipes)
{
	if (cmd_num > 0)
	{
		if (dup2(pipes[cmd_num - 1][0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (cmd_num < num_pipes)
	{
		if (dup2(pipes[cmd_num][1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(EXIT_FAILURE);
		}
	}
	ft_close_pipes(pipes, num_pipes);
	execvp(args[0], args);
	exit(EXIT_SUCCESS);
}

void	ft_create_and_manage_process(char **args, int **pipes, int cmd_num, int num_pipes, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		ft_handle_child_process(args, pipes, cmd_num, num_pipes);
	else
	{
		waitpid(*pid, NULL, 0);
		if (cmd_num < num_pipes)
			close(pipes[cmd_num][1]);
		if (cmd_num > 0)
			close(pipes[cmd_num - 1][0]);
	}
}

// void free_args(char** args) {
//     if (args != NULL) {
//         for (int i = 0; args[i] != NULL; i++) {
//             free(args[i]);
//         }
//         free(args);
//         args = NULL;
//     }
// }

int	ft_exect_pipes(t_minishell *ms)
{
	int		i, cmd_start, cmd_num;
	pid_t	pid;
	int		**pipes;

	int num_pipes = ft_count_pipes(ms, ms->tokens);
	if (num_pipes == 0 || !(pipes = ft_allocate_pipes(num_pipes)))
		return (EXIT_FAILURE);
	cmd_start = cmd_num = i = 0;
	while (ms->tokens[i])
	{
		if ((!ms->token.protected[i] && ft_strcmp(ms->tokens[i], "|") == 0) || ms->tokens[i + 1] == NULL)
		{
			if (ms->tokens[i + 1] == NULL)
				i++;
			char **args = ft_extract_args(ms->tokens, cmd_start, i);
			ft_create_and_manage_process(args, pipes, cmd_num, num_pipes, &pid);
			free(args);
			cmd_start = i + 1;
			cmd_num++;
		}
		i++;
	}
	ft_close_pipes(pipes, num_pipes);
	return (EXIT_SUCCESS);
}
