/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 13:23:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(t_minishell *ms, char *cmd)
{
	if (errno == EACCES)
	{
		ft_fprintf(2, "ms: %s\n", strerror(errno));
		ms->ret = CPERM_DENIED;
	}
	else if (errno == ENOENT)
	{
		ft_fprintf(2, "ms: command not found: %s\n", cmd);
		ms->ret = CMD_NOT_FOUND;
	}
	else
	{
		ft_fprintf(2, "ms: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
}

int	check_error_cd(t_minishell *ms)
{
	if (errno == EACCES)
	{
		ft_fprintf(2, "cd: %s\n", strerror(errno));
		ms->ret = CPERM_DENIED;
	}
	else if (errno == ENOTDIR)
	{
		ft_fprintf(2, "cd: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	else
	{
		ft_fprintf(2, "cd: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
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
		status = 128 + WTERMSIG(last_status);
	else if (WIFEXITED(last_status) && !WIFSIGNALED(last_status))
		status = WEXITSTATUS(last_status);
	else
		status = last_status;
	return (status);
}
