/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:19:36 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/20 16:39:48 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exect_pipes(t_minishell *ms)
{
	pid_t	pid;
	t_pipes	p;
	int		i;

	i = 0;
	init_pipes(&p);
	p.num_pipes = count_pipes(ms, ms->tokens);
	if (p.num_pipes == 0 || !(p.pipes = allocate_pipes(&p)))
		return (ERROR);
	p.cmd_start = i;
	p.cmd_num = 0;
	while (ms->tokens[i])
	{
		if ((is_pipe(ms->tokens[i]) && ms->token.protected[i] == 0) || ms->tokens[i + 1] == NULL)
		{
			if (ms->tokens[i + 1] == NULL)
			{
				i++;
				p.last_cmd = TRUE;
			}
			p.p_args = extract_args(ms->tokens, p.cmd_start, i);
			fill_pipes_protected_array(ms, &p, p.cmd_start);
			//print_arg_protected_array(&p);
			p.ret = create_and_manage_process(ms, &p, &pid);
			free(p.p_args);
			free_int_array(&p.arg_protected);
			p.cmd_start = i + 1;
			p.cmd_num++;
			if (p.last_cmd)
				break ;
		}
		i++;
	}
	close_pipes(&p);
	return (p.ret);
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

void	handle_child_process(t_minishell *ms, t_pipes *p)
{
	int	return_value;

	return_value = 0;
	if (p->cmd_num > 0)
	{
		if (dup2(p->pipes[p->cmd_num - 1][0], STDIN_FILENO) == -1)
		{
			ft_fprintf(2, "ms: dup2 stdin error: %s\n", strerror(errno));
			exit(FAIL);
		}
	}
	if (p->cmd_num < p->num_pipes)
	{
		if (dup2(p->pipes[p->cmd_num][1], STDOUT_FILENO) == -1)
		{
			ft_fprintf(2, "ms: dup2 stdout error: %s\n", strerror(errno));
			exit(FAIL);
		}
	}
	close_pipes(p);
	return_value = call_commands_pipes(ms, p);
	free(ms->cmd_path);
	exit_child(ms, return_value);
}

int	create_and_manage_process(t_minishell *ms, t_pipes *p, pid_t *pid)
{
	int	return_value;

	return_value = 0;
	*pid = fork();
	if (*pid == 0)
    	handle_child_process(ms, p);
	else
	{
		if (p->cmd_num < p->num_pipes)
			close(p->pipes[p->cmd_num][1]);
		if (p->cmd_num > 0)
			close(p->pipes[p->cmd_num - 1][0]);
	    return_value = wait_children();
	}
	return (return_value);
}

int	call_commands_pipes(t_minishell *ms, t_pipes *p)
{
	int	return_value;

	return_value = 0;
    if (!p->p_args)
	    exit_child(ms, 0);
	if (pipes_has_redirect(p) == TRUE)
	{
		if (exec_redirection_pipes(p, ms) != SUCCESS)
			exit_child(ms, 0);
	}
	return_value = detect_executable(ms, p->p_args);
	if (return_value == EXE_NOT_FOUND)
		return_value = exec_builtin2(ms, p->p_args, 1);
	if (return_value == CMD_NOT_FOUND)
		return_value = ft_execvp(p->p_args, ms->env);
	exit_child(ms, return_value);
	return (return_value);
}
