/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:31:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/24 12:43:23 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Free our variables, clear the history from readline, wait the child to
	finish and quit minishell with the return status of the last command.
*/
void	exit_minishell(t_minishell *ms)
{
	int	child_ret;

	ft_free_at_exit(ms);
	clear_history();
	while (waitpid(-1, &child_ret, 0) > 0)
		;
	ft_printf(BOLD GREEN "ms: Goodbye %s!\n" RESET BOLDRESET, ms->user);
	free(ms);
	exit(0);
}

void	exit_child(t_minishell *ms)
{
	ft_free_at_exit(ms);
	ft_free_tokens(ms->tokens);
	exit(ms->ret);
}

/*
	This function wait the children created in the fork.
	For each iteration of wait, until it gets an error(-1) and no code 10,
	it will wait the child to terminate and save the status in last status.
	At the end, we check the status to assign the appropriate return value
	to the final status :

	ECHILD = ECHILD : no child job (code 10) // stop the loop in we get this
	WIFSIGNALED = Child got kill by a signal
	WTERMSIG = if WIFSIGNALED we get the signum that killed the child
	WIFEXITED = Check if the child terminated normally
	WEXITSTATUS = If WIFEXITED we get the exit code of the child

	bash calculate the error return this way : 128 + signum
*/
int	wait_children(t_minishell *ms)
{
	pid_t	wait_pid;
	int		status;
	int		last_status;

	wait_pid = 0;
	last_status = 0;
	while (wait_pid != -1 || errno != ECHILD)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == ms->pid)
			last_status = status;
		else if (wait_pid != ms->pid)
			last_status = status;
	}
	if (WIFSIGNALED(last_status))
	{
		status = 128 + WTERMSIG(last_status);
	}
	else if (WIFEXITED(last_status) && !WIFSIGNALED(last_status))
		status = WEXITSTATUS(last_status);
	else
		status = last_status;
	return (status);
}
