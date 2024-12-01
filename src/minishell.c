/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:02:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/01 02:42:01 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ms->expanded = NULL;
	ms->tokc = 0;
	ms->ret = 0;
	ms->path = NULL;
	ms->interactive = TRUE;
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.size = 1;
	ms->token.is_meta = FALSE;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.quoted = NULL;
	ms->in_pipe = FALSE;
	ms->pid = 0;
	ms->received_sig = 0;
	init_heredoc_data(ms);
}

/*
	- tokens_creator -> success: 0 | syntax_error: 2
		if ms->tokens is null, we do nothing and return 0
		(tokens_creator return 0 if no syntax errors were found)
	- heredoc -> success: 0 | terminated with SIGINT: 130
	- call_commands -> Return value depend of child return value.

	to do: rename to parse_input
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

/*
	Execute the prompt in a loop. We read the input with readline and store
	the input in ms->input. If readline do not encounter EOF(Ctrl+d), otherwise,
	we parse the input:

	1- Tokenizer: If line is empty, ms->tokens is null. Otherwise, separe the
		tokens at each unquoted blank character and meta-characters.

	2- Transformer : call the following:

		2.1- Expander: Iter in each tokens and expand the variables.

		2.2- Cleaner: Iter in each tokens and remove the empty tokens resulted
				from expander.

		2.3- Fill the int array ms->token.quoted which save the states of
				each token to determine if it was quoted or not.
				quoted: 1 | else: 0
		2.4 - Trimmer: Iter in each tokens and remove the quotes when needed.

	3-  we check if we have a heredoc, if so we execute and fill all heredocs at
		once and save them with an unique name in our folder /tmp.

	4-  if all the previous step were successful, we check if the tokens contain
		at least one pipe. If yes, execute the pipeline in exec_pipes and return
		the exitcode of the last command.

	5-	If the tokens contains no pipes, we execute the simple command in a
		sub-shell. Both pipes and simple command proceed like the following:

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

	5 - We free the history and other data to be ready for the next command.
*/
void	execms(t_minishell *ms, char **envp)
{
	ms->env = ft_envdup(envp);
	ms->path = getcwd(NULL, 0);
	// setenv("INPUTRC", "./.inputrc", 1);
	// set_env_var(ms, "INPUTRC", "./.inputrc");
	while (1)
	{
		sync_signals(ms);
		ms->prompt_name = get_prompt_name(ms);
		ms->input = readline(ms->prompt_name);
		if (!ms->input)
			break ;
		else if (*(ms->input) != '\0')
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
	init_signals_interactive(ms);
	execms(ms, envp);
	exit_minishell(ms, 0);
	return (0);
}
