
#include "commands.h"

/*
	Check if there if the tokens contains a pipe, if yes, execute all the commands.
	If there is no pipes, execute redirections if applicable, check if the command is
	an executable. If its not an executable, search the command in the paths. Return the
	exit status of the child process.

	to do:
	- ft_getenv
	- ft_setenv
	- export
	- unset
	- rework all commands (unless executable)

*/
int	call_commands(t_minishell *ms)
{
	int	pid;

	if (has_pipe(ms, ms->tokens) == TRUE)
	{
		ms->ret = ft_exect_pipes(ms);
		return (ms->ret);
	}
	pid = fork();
	if (pid < 0)
		return (ERROR);
	else if (pid == 0)
	{
		if (has_redirect(ms, ms->tokens))
		{
			if (exec_redirection(ms) != SUCCESS)
				exit_child(ms);
		}
		ms->ret = detect_executable(ms);
		if (ms->ret == EXE_NOT_FOUND)
			ms->ret = ft_execvp(ms->tokens, ms->env);
		exit_child(ms);
	}
	ms->ret = wait_children();
	return (ms->ret);
}

/*
	Execute a command in the path returned by find_executable_path.
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
			path = get_path(tokens[k]);
		if (!path || execve(path, tokens, envp) == FAIL)
		{
			ft_free(path);
			return (check_error(tokens[k]));
		}
		k++;
	}
	ft_free(path);
	return (SUCCESS);
}

/*
	Commands that must be call in the parent process to work (for now).
	Return SUCCESS(0) if the command is successful and CMD_NOT_FOUND(127)
	if the command it not in this function, so we can use this value to
	tell the program to search in paths.

	to do:
	- add unset without option
	- add export without option
	- rework pwd to display the same pwd in the environment variables
	  and need to work (not crash minishell) when we deleted the current directory
	- rework cd (need to update the pwd and old pwd in the environment variables)
	- rework exit (need to no exit the minishell if in pipe(exit child instead))
	- rework echo (should not display the path of heredocs and redirections)
	- rework env (should not display "env: success" if the first command in pipe
*/
int	exec_builtin(t_minishell *ms)
{
	if (is_exit(ms->tokens[0]))
	{
		free_tokens(ms->tokens);
		exit_minishell(ms);
	}
	ms->ret = detect_cd_call(ms);
	if (ms->ret == CMD_NOT_FOUND)
	{
		ms->ret = detect_pwd_call(ms);
	}
	if (ms->ret == CMD_NOT_FOUND)
	{
		ms->ret = detect_env_call(ms);
	}
	if (ms->ret == CMD_NOT_FOUND)
	{
		ms->ret = detect_echo_call(ms);
	}
	return (ms->ret);
}
