/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 13:09:58 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_call_commands(char **args, char **envp)
{
    int pid;
	int	child_ret;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (ft_exec_commands(args, envp) != SUCCESS)
			exit(1);
	}
	waitpid(pid, &child_ret, 0);
}

int	ft_exec_commands(char **args, char **envp)
{
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_custom_cmds(args, envp) == SUCCESS)
			return (SUCCESS);
		else
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
		// Execute un executable
		if (ft_strnstr(args[i], "./", 2))
		{
			execve(args[i], args, envp);
			return (SUCCESS);
		}
		// To do
		else if (ft_strnstr(args[i], "echo -n", 7))
		{
            // faire leffet % surligner du vrai echo -n
			ft_printf(SURL "%\n" SURLRESET);
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}
