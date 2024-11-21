/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:19:36 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 14:15:45 by ccodere          ###   ########.fr       */
=======
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:19:36 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/20 16:39:48 by matislessar      ###   ########.fr       */
>>>>>>> origin/cmd
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exect_pipes(t_minishell *ms)
{
	pid_t	pid;
	int		i;

	init_exec_pipes(ms, &i);
	while (ms->tokens[i])
	{
		if ((is_pipe(ms->tokens[i]) && ms->token.protected[i] == 0)
			|| ms->tokens[i + 1] == NULL)
		{
			handle_last_cmd(ms, &i);
			handle_pipe_cmd(ms, i, &pid);
			if (ms->p.last_cmd)
				break ;
		}
		i++;
	}
	close_pipes(ms);
	ms->ret = wait_children();
	return (ms->p.ret);
}

void	handle_pipe_cmd(t_minishell *ms, int i, pid_t *pid)
{
    ms->p.p_args = extract_args(ms->tokens, ms->p.cmd_start, i);
	if (!ms->p.p_args)
		return ;
		
    fill_pipes_protected_array(ms, ms->p.cmd_start);
    ms->p.ret = create_and_manage_process(ms, pid);
	free(ms->p.p_args);
	ms->p.p_args = NULL;
	free_int_array(&ms->p.arg_protected);
	ms->p.cmd_start = i + 1;
    ms->p.cmd_num++;
}

void	handle_child_process(t_minishell *ms)
{
	int	return_value;

	return_value = 0;
	if (pipes_redirection(ms) != SUCCESS)
		exit_child(ms, 42);
	if (has_type(ms->p.p_args, &ms->p.arg_protected, is_redirect)
		|| has_type(ms->p.p_args, &ms->p.arg_protected, is_heredoc))
	{
		ms->ret = exec_redirections(ms, ms->p.p_args, &ms->p.arg_protected, TRUE);
		if (ms->ret > 0)	
			exit_child(ms, ms->ret);
	}
	close_pipes(ms);
	return_value = call_commands_pipes(ms);
	exit_child(ms, return_value);
}

int	create_and_manage_process(t_minishell *ms, pid_t *pid)
{
	int	return_value;

	return_value = 0;
	*pid = fork();
	if (*pid == -1)
		return(FAIL);
	else if (*pid == 0)
		handle_child_process(ms);
	else
	{
		if (ms->p.cmd_num < ms->p.num_pipes)
			close(ms->p.pipes[ms->p.cmd_num][1]);
		if (ms->p.cmd_num > 0)
			close(ms->p.pipes[ms->p.cmd_num - 1][0]);
	}
	return (return_value);
}

int	call_commands_pipes(t_minishell *ms)
{
	int return_value;

	return_value = 0;
	if (!ms->p.p_args || !ms->p.p_args[0])
		exit_child(ms, 0);
	return_value = detect_executable(ms, ms->p.p_args);
	if (return_value == EXE_NOT_FOUND)
		return_value = exec_builtin2(ms, ms->p.p_args, 1);
	if (return_value == CMD_NOT_FOUND)
		return_value = ft_execvp(ms->p.p_args, ms->env);
	exit_child(ms, return_value);
	return (return_value);
}
