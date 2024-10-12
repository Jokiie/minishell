/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 04:00:01 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
Create a child process to execute a command
I added all the macros for child process return value, to check what it does and
I removed the custom command because it must be executed by the parent process.
Need to remove the check when we will finish the project or move it to respect
the norm.
*/
// int	exit_code;
// int	signal_num;
// if (WIFEXITED(child_ret))
// 	ft_printf("Child process terminated gracefully.\n");
// if (WIFEXITED(child_ret))
// {
// 	exit_code = WEXITSTATUS(child_ret);
// 	ft_printf("Child exit code : %d\n", exit_code);
// }
// if (WIFSIGNALED(child_ret))
// 	ft_printf("Child process got kill by a signal.\n");
// if (WIFSIGNALED(child_ret))
// {
// 	signal_num = WTERMSIG(child_ret);
// 	ft_printf("Child process got kill by the signal : %d\n", signal_num);
// }
void	ft_call_commands(t_minishell *ms)
{
	int	pid;
	int	child_ret;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		ft_exec_redirection(ms);
		if (ft_exec_commands(ms, ms->tokens) != SUCCESS)
			exit(1);
	}
	wait(&child_ret);
}

t_bool	ft_call_custom_cmds(t_minishell *ms)
{
	if (ft_custom_cmds(ms) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

t_bool	ft_exec_commands(t_minishell *ms, char **tokens)
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
		if (execve(path, tokens, ms->env) == -1)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

t_bool	ft_custom_cmds(t_minishell *ms)
{
	int	i;

	i = 0;
	if (!ms->tokens)
		return (FAIL);
	while (ms->tokens[i])
	{
		if (ft_strnstr(ms->tokens[0], "cd", 2))
		{
			cd(ms->tokens);
			return (SUCCESS);	
		}
		if (ft_strnstr(ms->tokens[0], "pwd", 3))
		{
			pwd(ms->tokens);
			return (SUCCESS);
		}
		if (detect_echo_call(ms->tokens, i) == SUCCESS)
			return (SUCCESS);
		if (ft_strnstr(ms->tokens[i], "./", 2))
		{
			if (execve(ms->tokens[i], ms->tokens, ms->env) == -1)
				ft_fprintf(2, "ms: no such file or directory: %s\n",
					ms->tokens[i]);
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}
