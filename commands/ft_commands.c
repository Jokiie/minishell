
#include "commands.h"

/*
	tokens_creator -> 0 : Success / 1 : Error / 2 : Syntaxe
	external_cmds  -> 0 : Success / 1 : Error / 127 : CmdNotfound
	call_commands  -> if built-in commands return CMD_NOT_FOUND(127),
	call_commands is called by the child process. Return value depend of
	child return value.
*/
int	execute_input(t_minishell *ms, char *input)
{
	ms->ret = tokens_creator(ms, input);
	if (ms->ret == SUCCESS && ms->tokens)
	{
		if (execute_heredocs(ms) == ERROR)
			return (ERROR);
		//print_debug(ms->tokens);
		ms->ret = exec_builtin(ms);
		if (ms->ret == CMD_NOT_FOUND)
			ms->ret = call_commands(ms);
		free_tokens(ms->tokens);
	}
	return (ms->ret);
}
/*
	Create a child process with fork to execute a command in the environment
	path variable. wait_children wait the children processes to finish and
	save their return value. We check if forked_builtin_cmds return ERROR
	because if the token is not executable, it have a special message and
	if we returned CMD_NOT_FOUND(127), and checkit like for built-in
	commands, it will show the wrong message. 

	to do:
	- handle "<<"
	- create our own get_env (to get added variables from our environment)
	

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
		{
			ms->ret = exec_builtin(ms);
			if (ms->ret == CMD_NOT_FOUND)
				ms->ret = ft_execvp(ms->tokens, ms->env);
		}
		else
			exit_child(ms);
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
			path = find_executable_path(tokens[k]);
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
	tell the program to search in forked built-in commands and bash
	commands.

	to do:
	- add unset without option
	- add export without option
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
