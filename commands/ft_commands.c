
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
		//ft_print_tokens(ms->tokens);
		ms->ret = built_in_cmds(ms);
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
	save their return value. We check if forked_builtin_cmds return ERROR
	because if the token is not executable, it have a special message and
	if we returned CMD_NOT_FOUND(127), and checkit like for built-in
	commands, it will show the wrong message. 

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
		if (ft_has_pipe(ms->tokens) == 0)
			ft_exect_pipes(ms);
		if (ms->ret == CMD_NOT_FOUND)
			ms->ret = forked_builtin_cmds(ms);
		if (built_in_cmds(ms) != ERROR)
		{
			ms->ret = exec_path_cmds(ms, ms->tokens, 0);
			exit_child(ms);
		}
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
int	exec_path_cmds(t_minishell *ms, char **tokens, int k)
{
	char	*path;
	char	*cmd;

	if (!ms->tokens || !*(ms->tokens))
		return (0);
	while (tokens[k])
	{
		if (*tokens[0] == '/')
		{
			cmd = get_last_dir(tokens[k]);
			path = find_executable_path(cmd);
			ft_free(cmd);
		}
		else
			path = find_executable_path(tokens[k]);
		if (!path || execve(path, tokens, ms->env) == FAIL)
		{
			ft_free(path);
			ms->ret = check_error(ms, tokens[k]);
			return (ms->ret);
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
int	built_in_cmds(t_minishell *ms)
{
	int	k;

	k = 0;
	if (!ms->tokens || !*(ms->tokens))
		return (SUCCESS);
	while (ms->tokens[k])
	{
		if ((k == 0) && ft_strncmp(ms->tokens[k], "exit\0", 5) == 0
			&& !ms->tokens[k + 1])
		{
			ft_free_tokens(ms->tokens);
			exit_minishell(ms);
		}
		if (detect_cd_call(ms, k) != CMD_NOT_FOUND
			|| detect_pwd_call(ms, k) != CMD_NOT_FOUND
			|| detect_env_call(ms, k) != CMD_NOT_FOUND
			|| detect_echo_call(ms, k) != CMD_NOT_FOUND)
			return (ms->ret);
		k++;
	}
	ms->ret = CMD_NOT_FOUND;
	return (ms->ret);
}

/*
	These commands need to be called in call_commands because it will be called
	twice if not found in our functions and in the bash. If they dont exist they
	write both error message from the find_executable_path and from bash. If the
	command is not in this function, return CMD_NOT_FOUND(127), so the fork can
	search the commands in the paths. Else, return 0 for success and 1 for
	errors so the fork dont search in the paths.

	-> echo and env is here because it do no work with redirection otherwise.
	
	/!\ Each command should return an int to get the return value. We need it
		for the "$?" commands which print the return value of the last command.
		We save the return value of a command in ms->ret.
*/
int	forked_builtin_cmds(t_minishell *ms)
{
	int	k;

	k = 0;
	if (!ms->tokens || !(*ms->tokens))
		exit_child(ms);
	while (ms->tokens[k])
	{
		if (detect_executable(ms, k) != ERROR)
			return (ms->ret);
		k++;
	}
	ms->ret = ERROR;
	return (ms->ret);
}
