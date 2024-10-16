/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/16 11:37:35 by ccodere          ###   ########.fr       */
=======
/*   Updated: 2024/10/16 11:32:20 by ccodere          ###   ########.fr       */
>>>>>>> tokenizer
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	parse_prompt(t_minishell *ms, char *prompt)
{
	if (ft_create_tokens(ms, prompt) == SUCCESS)
	{
<<<<<<< HEAD
		// ft_print_tokens(ms->tokens);
=======
		ft_print_tokens(ms->tokens);
>>>>>>> tokenizer
		if (external_cmds(ms) != SUCCESS)
			call_commands(ms);
	}
	add_history(prompt);
	return (ERROR);
}

/*
	Create a child process with fork to execute a command in the environment
	path variable.
	to do:
	- Maybe process the redirection during the lexing, while reading
		meta-characters.
		handle "<<" ">>" "|"
*/
void	call_commands(t_minishell *ms)
{
	int	pid;
	int	child_ret;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		signal(SIGINT, ft_sigint_handler);
		signal(SIGQUIT, ft_sigquit_handler);
		ft_exec_redirection(ms);
		if (built_in_cmds(ms) != SUCCESS)
		{
			exec_cmd_in_paths(ms, ms->tokens, 0);
			exit_child(ms);
		}
		exit_child(ms);
	}
	wait(&child_ret);
}

int	exec_cmd_in_paths(t_minishell *ms, char **tokens, int i)
{
	char	*path;
	char	*cmd;

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
		if (!path || execve(path, tokens, ms->env) == -1)
		{
			ft_free(path);
			return (FAIL);
		}
		i++;
	}
	ft_free(path);
	return (SUCCESS);
}

/* Commands that must be call in the parent process to work */
int	external_cmds(t_minishell *ms)
{
	int	k;

	k = 0;
	while (ms->tokens[k])
	{
		if (ft_strnstr(ms->tokens[0], "exit", 4) && !ms->tokens[k + 1])
			exit_minishell(ms);
		if (detect_cd_call(ms) == SUCCESS)
			return (SUCCESS);
		k++;
	}
	return (FAIL);
}

/*	to do:
	- add "env" command without option or argument(printf ms->env)
	- add unset without option
	- add export without option
	- these commands need to be called in built_in_cmds because it
		will be called twice if used in the fork(if they dont exist they
		write both error message from the ft_check_n_create_path and from
		the related command).
	- Each command should return a int to get the return value. We will
		need it for the "$?" commands which print the return value of the
		last command.
*/
int	built_in_cmds(t_minishell *ms)
{
	int	k;

	k = 0;
	if (!ms->tokens)
		return (FAIL);
	while (ms->tokens[k])
	{
		if (detect_pwd_call(ms, ms->tokens) == SUCCESS)
			return (SUCCESS);
		if (detect_echo_call(ms->tokens, k) == SUCCESS)
			return (SUCCESS);
		if (detect_executable(ms, ms->tokens, k) == SUCCESS)
			return (SUCCESS);
		k++;
	}
	return (FAIL);
}
