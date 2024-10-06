/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/05 23:47:01 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Create a child process to execute a command
*/
void	ft_call_commands(char **tokens, char **envp)
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
		if (ft_exec_commands(tokens, envp) != SUCCESS)
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
}

int	ft_call_custom_cmds(char **tokens, char **envp)
{
	if (ft_custom_cmds(tokens, envp) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int	ft_exec_commands(char **tokens, char **envp)
{
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	if (!tokens)
		return (FAIL);
	while (tokens[i])
	{
		if (*tokens[0] == '/')
		{
			cmd = ft_get_last_dir(tokens[i]);
			path = ft_create_n_check_path(cmd);
		}
		else
			path = ft_create_n_check_path(tokens[i]);
		if (execve(path, tokens, envp) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_custom_cmds(char **tokens, char **envp)
{
	int	i;

	i = 0;
	if (!tokens)
		return (FAIL);
	while (tokens[i])
	{
		if (ft_strnstr(tokens[0], "cd", 2))
		{
			cd(tokens);
			return (SUCCESS);
		}
		else if (ft_strnstr(tokens[0], "pwd", 3))
		{
			pwd(tokens);
			return (SUCCESS);
		}
		if (ft_strnstr(tokens[i], "./", 2))
		{
			execve(tokens[i], tokens, envp);
			return (SUCCESS);
		}
		if (ft_strnstr(tokens[i], "echo", 4) && ft_strnstr(tokens[i + 1], "-n",
				2))
		{
			echo_n(tokens);
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}
