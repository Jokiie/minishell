/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:23:54 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 01:28:26 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	4-  if all the previous step were successful, we check if the tokens contain
		at least one pipe. If yes, execute the pipeline in exec_pipes. But will
		return the exit code of the last command to the next.

	5-	If the tokens contains no pipes, we execute the simple command in a
		sub-shell. Both pipelines and simple command proceed like the following:

		5.1-	We check if the command exist in our built-in(except echo)
				if the command exist, execute it and return SUCCESS or ERROR

		5.2-	If not found in our built-in, We create a fork in handle_child()
				and check if the tokens contains redirections or heredocs
				characters. If yes, we iter in the tokens and redirect the
				output/input depending of the meta characters. Then we recreate
				the tokens without these characters and argument(files).

		5.3-	We recheck the built-in to be sure we don't call the command in
				the system environment and include echo this time, so echo can
				print the tokens without the redirections or heredocs.

		5.4-	If we didn't find the command in our built-in, we check if it's
				an executable. If yes, we execute path directly with exerve.

		5.5- 	If not, we finally search the command in the environment path,
				and	execute it if found, otherwise we return the exit code from
				check_error.

		5.6 - We finally return the exit code of the child and return in execms.
*/
int	call_commands(t_minishell *ms)
{
	if (has_type(ms->tokens, &ms->token.quoted, &ms->token.expanded, is_pipe))
	{
		ms->ret = exect_pipes(ms);
		return (ms->ret);
	}
	if (ft_strncmp(ms->tokens[0], "exit\0", 5) == 0)
	{
		ft_exit(ms, ms->tokens, 0);
		return (ms->ret);
	}
	ms->ret = exec_builtin(ms, ms->tokens);
	if (ms->ret == CMD_NOT_FOUND)
	{
		ms->pid = fork();
		if (ms->pid < 0)
			return (ERROR);
		else if (ms->pid == 0)
		{
			handle_child(ms);
		}
		ms->ret = wait_children(ms);
	}
	return (ms->ret);
}

void	handle_child(t_minishell *ms)
{
	if (has_type(ms->tokens, &ms->token.quoted, &ms->token.expanded, is_heredoc)
		|| has_type(ms->tokens, &ms->token.quoted, &ms->token.expanded, is_redirect))
	{
		if (exec_redirections(ms, ms->tokens, &ms->token.quoted, &ms->token.expanded, FALSE) != 0)
			exit_child(ms, ERROR, FALSE);
	}
	if (!ms->tokens || !*ms->tokens)
		exit_child(ms, 0, FALSE);
	ms->ret = detect_echo_call(ms, ms->tokens);
	if (ms->ret == CMD_NOT_FOUND)
		ms->ret = detect_executable(ms, ms->tokens);
	if (ms->ret == EXE_NOT_FOUND)
		ms->ret = ft_execvp(ms->tokens, ms->env);
	exit_child(ms, ms->ret, FALSE);
}

/*
	Execute a command in the path returned by get_path.
	If path is accessible, we execute it and return SUCCESS(0), else, we free
	the path and return the error code returned by check error.
*/
int	ft_execvp(char **tokens, char **envp)
{
	char	*path;
	int		k;

	k = 0;
	while (tokens[k])
	{
		if (tokens[k][0] == '/')
			path = ft_strdup(tokens[k]);
		else
			path = get_path(envp, tokens[k]);
		if (!path || execve(path, tokens, envp) == FAIL)
		{
			free_ptr(path);
			return (check_error(tokens[k]));
		}
		k++;
	}
	free_ptr(path);
	return (SUCCESS);
}

/*
	Commands that must be call in the parent process to work (for now).
	Return SUCCESS(0) if the command is successful and CMD_NOT_FOUND(127)
	if the command it not in this function, so we can use this value to
	tell the program to search in paths.

	to do:
	- rework pwd to display the same pwd in the environment variables
		and need to rework (not crash minishell) when we deleted the current
		directory
	- rework cd (need to update the pwd and old pwd in the environment variables)
*/
int	exec_builtin(t_minishell *ms, char **tokens)
{
	int	ret;

	ret = 0;
	ret = detect_cd_call(ms, tokens);
	if (ret == CMD_NOT_FOUND)
		ret = detect_pwd_call(ms, tokens);
	if (ret == CMD_NOT_FOUND)
		ret = detect_env_call(ms, tokens);
	if (ret == CMD_NOT_FOUND)
		ret = detect_export_call(ms, tokens);
	if (ret == CMD_NOT_FOUND)
		ret = detect_unset_call(ms, tokens);
	return (ret);
}
