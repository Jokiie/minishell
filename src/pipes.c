/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/14 13:28:17 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	return_value = 0;

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
	ms->cmd_path = get_path(p->p_args[0]);
	return_value = call_commands_pipes(ms, p);
	free(ms->cmd_path);
	exit(return_value);
}

int	create_and_manage_process(t_minishell *ms, t_pipes *p, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		handle_child_process(ms, p);
	else
	{
		return_value = wait_children();
		if (p->cmd_num < p->num_pipes)
			close(p->pipes[p->cmd_num][1]);
		if (p->cmd_num > 0)
			close(p->pipes[p->cmd_num - 1][0]);
	}
	return (return_value);
}

void	init_pipes(t_pipes *p)
{
	p->p_args = NULL;
	p->num_pipes = 0;
	p->cmd_num = 0;
	p->pipes = NULL;
}

void	tokenize_input1(t_minishell *ms)
{
	int		i;
	char	*token;

	ms->tokens = malloc(sizeof(char *) * 1024);
	i = 0;
	token = ft_strtok(ms->input, " \t\n|");
	while (token)
	{
		ms->tokens[i++] = strdup(token);
		token = ft_strtok(NULL, " \t\n|");
	}
	ms->tokens[i] = NULL;
}

void	recreate_pipes_args(t_pipes *p, int i)
{
	char	**new_args;
	int		k;

	new_args = (char **)malloc(sizeof(char *) * (i + 1));
	k = 0;
	while (k < i)
	{
		if (!is_redirect(p->p_args[k]))
			new_args[k] = p->p_args[k];
		k++;
	}
	new_args[k] = NULL;
	p->p_args = new_args;
}

int	exec_redirection_pipes(t_pipes *p)
{
	int	k;
	int	return_value;

	k = 0;
	return_value = 0;
	if (!p->p_args || !*p->p_args)
		return (ERROR);
	while (p->p_args[k])
	{
		if (is_append(p->p_args[k]))
		{
			return_value = append_output(p->p_args[k + 1]);
			break ;
		}
		else if (is_redirect_out(p->p_args[k]))
		{
			return_value = redirect_output(p->p_args[k + 1]);
			break ;
		}
		else if (is_redirect_in(p->p_args[k]))
		{
			return_value = redirect_input(p->p_args[k + 1]);
			break ;
		}
		k++;
	}
	recreate_pipes_args(p, k);
	return (return_value);
}

int	call_commands_pipes(t_minishell *ms, t_pipes *p)
{
	if (has_redirect(ms, p->p_args))
	{
		if (exec_redirection_pipes(p) != SUCCESS)
			exit_child(ms);
	}
	return_value = exec_builtin(ms);
	if (return_value == CMD_NOT_FOUND)
	return_value = detect_executable(ms);
	if (return_value == EXE_NOT_FOUND)
		return_value = ft_execvp(p->p_args, ms->env);
	return (return_value);
}

int	exect_pipes(t_minishell *ms)
{
	pid_t	pid;
	t_pipes	p;
	int		i;
	int		cmd_start;
	int		last_cmd;

	i = 0;
	last_cmd = 0;
	init_pipes(&p);
	p.num_pipes = count_pipes(ms, ms->tokens);
	if (p.num_pipes == 0 || !(p.pipes = allocate_pipes(&p)))
		return (ERROR);
	cmd_start = i;
	p.cmd_num = 0;
	while (ms->tokens[i])
	{
		if ((ms->token.protected[i] == 0 && ft_strcmp(ms->tokens[i], "|") == 0)
			|| ms->tokens[i + 1] == NULL)
		{
			if (ms->tokens[i + 1] == NULL)
			{
				i++;
				last_cmd = 1;
			}
			p.p_args = extract_args(ms->tokens, cmd_start, i);
			return_value = create_and_manage_process(ms, &p, &pid);
			free(p.p_args);
			cmd_start = i + 1;
			p.cmd_num++;
			if (last_cmd)
				break ;
		}
		i++;
	}
	close_pipes(&p);
	return (return_value);
}
