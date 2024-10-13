/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/13 03:49:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Create a child process with fork to execute a command in the environment
	path variable.
	to do:
	- Maybe process the redirection during the lexing, while reading
		meta-characters.
		handle "<<" ">>" "|"
*/
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
			exit(FAIL);
	}
	wait(&child_ret);
}

int	ft_call_custom_cmds(t_minishell *ms)
{
	if (ft_custom_cmds(ms) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int	ft_exec_commands(t_minishell *ms, char **tokens)
{
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	if (!tokens || !*tokens)
		return (FAIL);
	while (tokens[i])
	{
		if (*tokens[0] == '/')
		{
			cmd = ft_get_last_dir(tokens[i]);
			path = ft_create_n_check_path(cmd);
			ft_free(cmd);
		}
		else
			path = ft_create_n_check_path(tokens[i]);
		if (execve(path, tokens, ms->env) == -1)
		{
			ft_free(path);
			return (FAIL);
		}
		i++;
	}
	ft_free(path);
	return (SUCCESS);
}

/*	to do:
	- add "env" command without option or argument(printf ms->env)
	- add "exit" without option , which quit minishell like shell.
	- add unset without option
	- add export without option
	- these commands need to be called in call_custom_cmds because it
		will be called twice if used in the fork(if they dont exist they
		write both error message from the ft_check_n_create_path and from
		the related command).
	- Each command should return a int to get the return value. We will
		need it for the "$?" commands which print the return value of the
		last command.
*/
int	ft_custom_cmds(t_minishell *ms)
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
				ft_fprintf(ms->std_err, "ms: no such file or directory: %s\n",
					ms->tokens[i]);
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}
