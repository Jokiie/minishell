/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:40:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 13:58:29 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	tokens_creator -> 0 : Success / 1 : Error / 2 : Syntaxe
	external_cmds  -> 0 : Success / 1 : Error / 127 : CmdNotfound
	call_commands  -> if built-in commands return CMD_NOT_FOUND(127),
	call_commands is called by the child process. Return value depend of
	child return value.
*/
int	parse_input(t_minishell *ms, char *input)
{
	ms->ret = tokens_creator(ms, input);
	if (ms->ret == SUCCESS)
	{
		ft_print_tokens(ms->tokens);
		ms->ret = external_cmds(ms);
		if (ms->ret == CMD_NOT_FOUND)
			ms->ret = call_commands(ms);
		ft_free_tokens(ms->tokens);
		return (ms->ret);
	}
	return (ms->ret);
}

/*
	Create a child process with fork to execute a command in the environment
	path variable. wait_children wait the children processes to finish and
	save their return value.
	to do:
	- handle "<<" ">>" "|"
*/
int	call_commands(t_minishell *ms)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (ERROR);
	else if (pid == 0)
	{
		ft_exec_redirection(ms);
		ms->ret = built_in_cmds(ms);
		if (ms->ret == CMD_NOT_FOUND)
		{
			ms->ret = exec_path_cmds(ms, ms->tokens, 0);
			exit_child(ms);
		}
		exit_child(ms);
	}
	ms->ret = wait_children(ms);
	return (ms->ret);
}

/*
	Execute a command in the path returned by find_executable_path.
	If path is accessible, with execute it and return SUCCESS(0), else, we free
	the path and return the error code returned by check error.
*/
int	exec_path_cmds(t_minishell *ms, char **tokens, int i)
{
	char	*path;
	char	*cmd;

	if (!tokens || !*tokens)
		exit_child(ms);
	while (tokens[i])
	{
		if (*tokens[0] == '/')
		{
			cmd = get_last_dir(tokens[i]);
			path = find_executable_path(cmd);
			ft_free(cmd);
		}
		else
			path = find_executable_path(tokens[i]);
		if (!path || execve(path, tokens, ms->env) == FAIL)
		{
			ft_free(path);
			ms->ret = check_error(ms, tokens[i]);
			return (ms->ret);
		}
		i++;
	}
	ft_free(path);
	return (SUCCESS);
}

/*
	Commands that must be call in the parent process to work. Return SUCCESS(0) if
	the command is successful and CMD_NOT_FOUND if the command it not in this
	function, so we can use this value to tell the program to search in built-in
	commands and bash commands. if ms->tokens point to NULL,
		return CMD_NOT_FOUND,
	because bash return this because we can't find a empty string, right?
*/
int	external_cmds(t_minishell *ms)
{
	int	k;

	k = 0;
	if (!ms->tokens || !*(ms->tokens))
		return (CMD_NOT_FOUND);
	while (ms->tokens[k])
	{
		if (ft_strncmp(ms->tokens[0], "exit\0", 5) == 0 && !ms->tokens[k + 1])
		{
			ft_free_tokens(ms->tokens);
			exit_minishell(ms);
		}
		if (detect_cd_call(ms, ms->tokens) != CMD_NOT_FOUND)
			return (ms->ret);
		k++;
	}
	return (CMD_NOT_FOUND);
}

/*
	These commands need to be called in built_in_cmds because it will be called
	twice if used in the fork(if they dont exist they write both error message
	from the find_executable_path and from the related command).
	Return CMD_NOT_FOUND, if the command is not in this function,
		so the fork can
	search the commands in the paths. Else,
		return 0 for success and 1 for errors.

	/!\ Each command should return an int to get the return value. We need it
		for the "$?" commands which print the return value of the last command.
		We save the return value of a command in ms->ret.
	to do:
	- add "env" command without option or argument(printf ms->env)
	- add unset without option
	- add export without option
*/
int	built_in_cmds(t_minishell *ms)
{
	int	k;

	k = 0;
	if (!ms->tokens || !(*ms->tokens))
		return (CMD_NOT_FOUND);
	while (ms->tokens[k])
	{
		if (detect_pwd_call(ms, ms->tokens) != CMD_NOT_FOUND
			|| detect_echo_call(ms, ms->tokens, k) != CMD_NOT_FOUND
			|| detect_executable(ms, ms->tokens, k) != CMD_NOT_FOUND)
			return (ms->ret);
		k++;
	}
	return (CMD_NOT_FOUND);
}
