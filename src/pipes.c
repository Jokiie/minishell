/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/12 16:52:51 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_pipes(char **str)
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

int	count_pipes(char **str)
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

int	**allocate_pipes(t_pipes *p)
{
	int i;

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
	int i;
	int size;
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

void	close_pipes(t_pipes *p)
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

void	pipes_redirection(t_pipes *p)
{
	if (p->cmd_num > 0)
		dup2(p->pipes[p->cmd_num - 1][0], STDIN_FILENO);
	if (p->cmd_num < p->num_pipes)
		dup2(p->pipes[p->cmd_num][1], STDOUT_FILENO);
}

void	handle_child_process(t_minishell *ms, t_pipes *p)
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
	close_pipes(p);
	ms->cmd_path = find_executable_path(p->p_args[0]);
	execve(ms->cmd_path, p->p_args, ms->env);
	perror("minishell: execve");
	free(ms->cmd_path);
	exit(EXIT_FAILURE);
}

void	create_and_manage_process(t_minishell *ms, t_pipes *p, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		handle_child_process(ms, p);
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

void tokenize_input1(t_minishell *ms)
{
	ms->tokens = malloc(sizeof(char *) * 1024);
	int i = 0;
	char *token = strtok(ms->input, " \t\n|");

	while (token)
	{
		ms->tokens[i++] = strdup(token);
		token = strtok(NULL, " \t\n|");
	}
	ms->tokens[i] = NULL;
}

int exect_pipes(t_minishell *ms)
{
	int	i;
	int	cmd_start;
	pid_t pid;
	t_pipes	p;
	int		last_cmd;
	
	last_cmd = 0;
	i = 0;
	init_pipes(&p);
	p.num_pipes = count_pipes(ms->tokens);
	if (p.num_pipes == 0 || !(p.pipes = allocate_pipes(&p)))
		return (ERROR);
	cmd_start = i;
	p.cmd_num = 0;
	while (ms->tokens[i])
	{
		if (ft_strcmp(ms->tokens[i], "|") == 0 || ms->tokens[i + 1] == NULL)
		{
			if (ms->tokens[i + 1] == NULL)
			{
				last_cmd = 1;
				i++;
			}
			p.p_args = extract_args(ms->tokens, cmd_start, i);
			if (!p.p_args)
				return (EXIT_FAILURE);
			create_and_manage_process(ms, &p, &pid);
			free(p.p_args);
			cmd_start = i + 1;
			p.cmd_num++;
			if (last_cmd)
				break ;
		}
		i++;
	}
	if (p.num_pipes != 0)
		ms->ret = ERROR;
	else
		ms->ret = SUCCESS;
	printf("Exiting while loop\n");
	close_pipes(&p);
	return (ms->ret);
}
