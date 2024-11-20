/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/20 16:36:10 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_redirection_pipes(t_pipes *p, int k, int return_value)
{
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
	int	return_value;

	return_value = 0;
	if (has_redirect(ms, p->p_args))
	{
		if (exec_redirection_pipes(p, 0, 0) != SUCCESS)
			exit_child(ms, 0);
	}
	return_value = exec_builtin(ms, p->p_args, 1);
	if (return_value == CMD_NOT_FOUND)
		return_value = detect_executable(ms, p->p_args);
	if (return_value == EXE_NOT_FOUND)
		return_value = ft_execvp(p->p_args, ms->env);
	exit_child(ms, return_value);
	return (return_value);
}

int	exect_pipes(t_minishell *ms)
{
	pid_t	pid;
	t_pipes	p;
	int		i;
	int		cmd_start;
	int		last_cmd;
	int		return_value;

	i = 0;
	return_value = 0;
	last_cmd = 0;
	init_pipes(&p);
	p.num_pipes = count_pipes(ms, ms->tokens);
	if (p.num_pipes == 0 || !(p.pipes = allocate_pipes(&p)))
		return (ERROR);
	cmd_start = i;
	p.cmd_num = 0;
	while (ms->tokens[i])
	{
		if ((is_pipe(ms->tokens[i]) && ms->token.protected[i] == 0) || ms->tokens[i + 1] == NULL)
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
