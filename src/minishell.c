
#include "../includes/minishell.h"

/* init heredocs related data */
void	init_heredoc_data(t_minishell *ms)
{
	ft_bzero(ms->heredoc.fd_name, sizeof(ms->heredoc.fd_name));
	ms->heredoc.delim = NULL;
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
	ms->tokc = 0;
	ms->std_in = 0;
	ms->std_out = 1;
	ms->std_err = 2;
	ms->ret = 0;
	ms->path = NULL;
	ms->interactive = TRUE;
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.protected = NULL;
	ms->handled_heredoc = FALSE;
	ms->fd.fdin = NULL;
	ms->fd.fdout = NULL;
	ms->fd.saved_stdin = 0;
	ms->fd.saved_stdout = 0;
	init_heredoc_data(ms);
}

/*
	Execute the prompt in a loop and read the input with readline,
	then separe the string in token , search the path and execute the command
	if the path is found. Add_history allow us to click the up arrow key to
	reuse a command. It frees the input after each line so we don't have leaks
	or corrupted data.
*/

void	execms(t_minishell *ms, char **envp)
{
	ms->path = getcwd(NULL, 0);
	if (!ms->path)
		exit(EXIT_FAILURE);
	setenv("INPUTRC", "./.inputrc", 1);
	ms->env = ft_envdup(envp);
	// rl_bind_key('\t', rl_complete);
	while (1)
	{
		ms->prompt_name = get_prompt_name(ms);
		ms->input = readline(ms->prompt_name);
		if (!ms->input || is_exit(ms->input) == TRUE)
		{
			exit_minishell(ms);
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

	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ft_memset(ms, 0, sizeof(ms));
	(void)argv;
	if (argc == 1)
	{
		init_minishell(ms);
		init_signals_interactive();
		execms(ms, envp);
	}
	exit_minishell(ms);
	return (0);
}
