/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/04 17:50:07 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_has_pipe(char **str)
{
	int i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			if (strcmp(str[i], "|") == 0)
			{
				printf("pipes detected\n");
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}

int	ft_count_pipes(char **str)
{
	int i;
	int num_pipes;

	i = 0;
	num_pipes = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0)
			num_pipes++;
		i++;
	}
	return (num_pipes);
}

int	**ft_allocate_pipes(t_pipes *p)
{
	int i;

	p->pipes = malloc(sizeof(int *) * p->num_pipes);
	i = 0;
	while (i < p->num_pipes)
	{
		p->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(p->pipes[i]) == -1)
		{
			perror("minishell: pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (p->pipes);
}

char	**ft_extract_args(char **tokens, int start, int end)
{
	int i, size;
	char **args;

	size = end - start;
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

void	ft_close_pipes(t_pipes *p)
{
	int i;

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

void	ft_pipes_redirection(t_pipes *p)
{
	if (p->cmd_num > 0)
		dup2(p->pipes[p->cmd_num - 1][0], STDIN_FILENO);
	if (p->cmd_num < p->num_pipes)
		dup2(p->pipes[p->cmd_num][1], STDOUT_FILENO);
}

void	ft_handle_child_process(t_minishell *ms, t_pipes *p)
{
	if (p->cmd_num > 0)
	{
		if (dup2(p->pipes[p->cmd_num - 1][0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (p->cmd_num < p->num_pipes)
	{
		if (dup2(p->pipes[p->cmd_num][1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(EXIT_FAILURE);
		}
	}
	ft_close_pipes(p);
	ms->cmd_path = find_executable_path(p->p_args[0]);
	execve(ms->cmd_path, p->p_args, ms->env);
	perror("minishell: execve");
	free(ms->cmd_path);
	exit(EXIT_FAILURE);
}

void	ft_create_and_manage_process(t_minishell *ms, t_pipes *p, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		ft_handle_child_process(ms, p);
	else
	{
		waitpid(*pid, NULL, 0);
		if (p->cmd_num < p->num_pipes)
			close(p->pipes[p->cmd_num][1]);
		if (p->cmd_num > 0)
			close(p->pipes[p->cmd_num - 1][0]);
	}
}

void init_pipes(t_pipes *p)
{
	p->p_args = NULL;
	p->num_pipes = 0;
	p->cmd_num = 0;
	p->pipes = NULL;
}

int ft_exect_pipes(t_minishell *ms)
{
	int i, cmd_start;
	pid_t pid;
	t_pipes p;

	init_pipes(&p);
	p.num_pipes = ft_count_pipes(ms->tokens);
	if (p.num_pipes == 0 || !(p.pipes = ft_allocate_pipes(&p)))
		return (EXIT_FAILURE);
	cmd_start = i = 0;
	p.cmd_num = 0;
	while (ms->tokens[i])
	{
		if (ft_strcmp(ms->tokens[i], "|") == 0 || ms->tokens[i + 1] == NULL)
		{
			if (ms->tokens[i + 1] == NULL)
				i++;
			p.p_args = ft_extract_args(ms->tokens, cmd_start, i);
			ft_create_and_manage_process(ms, &p,&pid);
			free(p.p_args);
			cmd_start = i + 1;
			p.cmd_num++;
		}
		i++;
	}
	ft_close_pipes(&p);
	return (EXIT_SUCCESS);
}