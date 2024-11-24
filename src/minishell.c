
#include "../includes/minishell.h"

/* init heredocs related data */
void	init_heredoc_data(t_minishell *ms)
{
    ms->heredoc.fd_name = NULL;
	ms->heredoc.delim = NULL;
	ms->heredoc.input = NULL;
	ms->heredoc.line = NULL;
	ms->heredoc.count = 0;
	ms->heredoc.index = 0;
	ms->heredoc.in_quotes = FALSE;
}

/* init the minishell struct variables */
void	init_minishell(t_minishell *ms)
{
	ms->input = NULL;
	ms->prompt_name = NULL;
	ms->user = NULL;
	ms->cwd = NULL;
	ms->prev_cwd = NULL;
	ms->env = NULL;
	ms->tokens = NULL;
	ms->pretokens = NULL;
	ms->characterized = NULL;
	ms->tokc = 0;
	ms->ret = 0;
	ms->path = NULL;
	ms->interactive = TRUE;
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.protected = NULL;
	ms->fd.fdin = NULL;
	ms->fd.fdout = NULL;
	ms->fd.saved_stdin = 0;
	ms->fd.saved_stdout = 0;
	ms->in_pipe = FALSE;
	init_heredoc_data(ms);
}

/*
	Execute the prompt in a loop and read the input with readline,
	then separe the string in token , search the path and execute the command
	if the path is found. Add_history allow us to click the up arrow key to
	reuse a command. It frees the input after each line so we don't have leaks
	or corrupted data.
*/

/*
	tokens_creator -> 0 : Success / 1 : Error / 2 : Syntaxe
	external_cmds  -> 0 : Success / 1 : Error / 127 : CmdNotfound
	call_commands  -> if built-in commands return CMD_NOT_FOUND(127),
	call_commands is called by the child process. Return value depend of
	child return value.
*/
int	execute_input(t_minishell *ms, char *input)
{
	if (tokens_creator(ms, input) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	else if (ms->tokens && *ms->tokens)
	{
		if (has_heredoc(ms, ms->tokens))
		{
			ms->ret = process_heredocs(ms);
			if (ms->ret == ERROR || ms->ret == TERM_SIGINT)
			{
				free_tokens_address(&ms->tokens);
				return (ms->ret);
			}
		}
		ms->ret = call_commands(ms);
		if (has_heredoc(ms, ms->tokens))
			reset_heredoc(ms);
		free_tokens_address(&ms->tokens);
	}
	return (ms->ret);
}

void	execms(t_minishell *ms, char **envp)
{
	ms->env = ft_envdup(envp);
	ms->path = getcwd(NULL, 0);
	if (!ms->path)
		exit(EXIT_FAILURE);
	//ms->test = ft_envdup(envp);
	setenv("INPUTRC", "./.inputrc", 1);
	//set_env_var(ms, "INPUTRC", "./.inputrc");
	while (1)
	{
		ms->prompt_name = get_prompt_name(ms);
		ms->input = readline(ms->prompt_name);
		if (!ms->input)
		{
			break ;
		}
		if (*(ms->input) != '\0')
		{
			ms->ret = execute_input(ms, ms->input);
			add_history(ms->input);
		}
		free_data(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	(void)argv;
	if (argc > 1)
		return (0);
	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ft_memset(ms, 0, sizeof(ms));
	init_minishell(ms);
	init_signals_interactive();
	execms(ms, envp);
	exit_minishell(ms, 0);
	return (0);
}
