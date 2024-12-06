/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:36:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 00:10:50 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exect_pipes(t_minishell *ms)
{
	int	i;
	int	ret;

	ret = 0;
	init_exec_pipes(ms, &i);
	while (ms->tokens[i])
	{
		if ((is_pipe(ms->tokens[i]) && ms->token.quoted[i] == 0
			&& ms->token.expanded[i] == 0) || ms->tokens[i + 1] == NULL)
		{
			handle_last_cmd(ms, &i);
			handle_pipe_cmd(ms, i, &ms->pid);
			if (ms->p.last_cmd)
				break ;
		}
		i++;
	}
	close_pipes(ms);
	ret = wait_children(ms);
	return (ret);
}

void	handle_pipe_cmd(t_minishell *ms, int i, pid_t *pid)
{
	ms->p.p_args = extract_args(ms, ms->tokens, ms->p.cmd_start, i);
	if (!ms->p.p_args)
		return ;
	fill_pipes_quoted_arr(ms, ms->p.cmd_start);
	//print_int_array(ms->p.p_args, &ms->p.arg_quoted);
	fill_pipes_expanded_arr(ms, ms->p.cmd_start);
	//print_expanded_array(ms->p.p_args, &ms->p.arg_expanded);
	//write(2, "Pipes args:\n", 13);
	//print_debug(ms->p.p_args);
	ms->p.ret = create_and_manage_process(ms, pid);
	free(ms->p.p_args);
	ms->p.p_args = NULL;
	free_int_array(&ms->p.arg_quoted);
	free_int_array(&ms->p.arg_expanded);
	ms->p.cmd_start = i + 1;
	ms->p.cmd_num++;
}

void	handle_child_process(t_minishell *ms)
{
	int	ret;

	ret = ms->ret;
	if (pipes_redirection(ms) != SUCCESS)
		exit_child(ms, ret, TRUE);
	if (has_type(ms->p.p_args, &ms->p.arg_quoted, &ms->p.arg_expanded, is_redirect)
		|| has_type(ms->p.p_args, &ms->p.arg_quoted, &ms->p.arg_expanded, is_heredoc))
	{
		ret = exec_redirections(ms, ms->p.p_args, &ms->p.arg_quoted, &ms->p.arg_expanded, TRUE);
		if (ret > 0)
			exit_child(ms, ret, TRUE);
	}
	close_pipes(ms);
	ret = call_commands_pipes(ms);
	exit_child(ms, ret, TRUE);
}

int	create_and_manage_process(t_minishell *ms, pid_t *pid)
{
	int	return_value;

	return_value = 0;
	*pid = fork();
	if (*pid == -1)
		return (FAIL);
	else if (*pid == 0)
	{
		handle_child_process(ms);
	}
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
	int	ret;

	ret = 0;
	if (!ms->p.p_args || (!ms->p.p_args[0] && ms->p.arg_quoted[0] == 0))
		exit_child(ms, ret, TRUE);
	if (ft_strncmp(ms->p.p_args[0], "exit\0", 5) == 0)
	{
		ret = ft_exit(ms, ms->p.p_args, 1);
		return (ret);
	}
	ret = detect_echo_call(ms, ms->p.p_args);
	if (ret == CMD_NOT_FOUND)
		ret = detect_executable(ms, ms->p.p_args);
	if (ret == EXE_NOT_FOUND)
		ret = exec_builtin(ms, ms->p.p_args);
	if (ret == CMD_NOT_FOUND)
		ret = ft_execvp(ms->p.p_args, ms->env);
	return (ret);
}
