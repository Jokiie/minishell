/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 23:59:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Create a child process to execute a command
*/
void	ft_call_commands(char **args, char **envp)
{
	int	pid;
	int	child_ret;
	int	exit_code;
	int	signal_num;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (ft_exec_commands(args, envp) != SUCCESS)
			exit(1);
	}
	wait(&child_ret);
	if (WIFEXITED(child_ret))
		ft_printf("Child process terminated gracefully.\n");
	if (WIFEXITED(child_ret))
	{
		exit_code = WEXITSTATUS(child_ret);
		ft_printf("Child exit code : %d\n", exit_code);
	}
	if (WIFSIGNALED(child_ret))
		ft_printf("Child process got kill by a signal.\n");
	if (WIFSIGNALED(child_ret))
	{
		signal_num = WTERMSIG(child_ret);
		ft_printf("Child process got kill by the signal : %d\n", signal_num);
	}
	if (WIFSTOPPED(child_ret))
		ft_printf("Child process stopped.\n");
	if (WIFCONTINUED(child_ret))
		ft_printf("Child process continued\n");
	ft_printf("Child returned the value : %d\n", child_ret);
}

int	ft_call_custom_cmds(char **args, char **envp)
{
	if (ft_custom_cmds(args, envp) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int	ft_exec_commands(char **args, char **envp)
{
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	while (args[i])
	{
		if (*args[0] == '/')
		{
			cmd = ft_get_last_dir(args[i]);
			path = ft_create_n_check_path(cmd);
		}
		else
			path = ft_create_n_check_path(args[i]);
		if (execve(path, args, envp) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_custom_cmds(char **args, char **envp)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strnstr(args[0], "cd", 2))
		{
			cd(args);
			return (SUCCESS);
		}
		else if (ft_strnstr(args[0], "pwd", 3))
		{
			pwd(args);
			return (SUCCESS);
		}
		// Execute an executable
		if (ft_strnstr(args[i], "./", 2))
		{
			execve(args[i], args, envp);
			return (SUCCESS);
		}
		// To do, do not work right now
		else if (ft_strnstr(args[i], "echo -n", 7))
		{
			// Make the same highlight effect of % of the true 'echo -n'
			ft_printf(SURL "%\n" SURLRESET);
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}
