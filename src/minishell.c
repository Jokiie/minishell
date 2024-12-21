/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:02:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/21 01:18:42 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* init the minishell struct variables */

void	init_token_data(t_minishell *ms)
{
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.size = 1;
	ms->token.is_meta = FALSE;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.quoted = NULL;
	ms->token.expanded = NULL;
	ms->token.state_array = NULL;
	ms->token.state_array_size = 0;
	ms->token.state_array_capacity = 0;
	ms->token.state_index = 0;
	ms->token.new_state_array = NULL;
	ms->token.new_state_array_size = 0;
	ms->token.new_state_array_capacity = 0;
	ms->token.db_buffer = NULL;
	ms->token.db_capacity = 0;
	ms->token.db_size = 0;
	ms->token.expansion_start = 0;
	ms->token.expansion_end = 0;
	ms->token.expansion_len = 0;
	ms->token.expansion_state = 0;
	ms->token.quoted_state = 0;
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
	ms->in_pipe = FALSE;
	ms->pid = 0;
	ms->received_sig = 0;
	ms->isatty = 0;
	init_token_data(ms);
	init_heredoc_data(ms);
}

/*
	- tokens_creator -> success: 0 | syntax_error: 2
		if ms->tokens is null, we do nothing and return the last return value
		(tokens_creator return 0 if no syntax errors were found)
	- heredoc -> success: 0 | terminated with SIGINT: 130
	- call_commands -> Return value depend of the last command return value.
*/
int	execute_input(t_minishell *ms, char *input)
{
	if (tokens_creator(ms, input) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	else if (ms->tokens && *ms->tokens)
	{
		if (has_type(ms->tokens, &ms->token.quoted, &ms->token.expanded,
				is_heredoc))
		{
			ms->ret = process_heredocs(ms);
			if (ms->ret == ERROR || ms->ret == TERM_SIGINT)
			{
				free_tokens_address(&ms->tokens);
				return (ms->ret);
			}
		}
		ms->ret = call_commands(ms);
		if (has_type(ms->tokens, &ms->token.quoted, &ms->token.expanded,
				is_heredoc))
			reset_heredoc(ms);
		free_dbuffer(ms);
	}
	return (ms->ret);
}

/*
	Execute the prompt in a loop. We read the input with readline and store
	the input in ms->input. If readline do not encounter EOF(Ctrl+D),
	we parse the input:

	0- Tokens_creator: If line is empty or contain only spaces, ms->tokens is
		set to null, and we return 0. Otherwise, We check if we have an open
		quote, if so, we return SYNTAX_ERROR and do not proceed further.
		Otherwise, We call tokenizer and transformer, then verify if we have a
		syntax error. If no syntax error is found, we return SUCCESS, otherwise
		return SYNTAX_ERROR.

	1- Tokenizer: Separe the line in tokens when we find an unquoted space or
		a meta character. If the result is not NULL, we proceed further.

	2- Transformer : Init quoted and expanded int arrays, which save the state
					 of each token (quoted or not) and (expanded or not). then
					 call the following:
					 
		2.0- Parser: Create a int ** array named state_array, which save the quoted
					 state of each character. (0 normal, 1 sgl quote, 2 dbl quote)
					 for example:
					 echo
					 '$USER'hey$USER
					 "$USER"
					 is represented in the map:
					 [0][0][0][0]
					 [1][1][1][1][1][1][1][0][0][0][0][0][0][0][0]
					 [2][2][2][2][2][2][2]

		2.1- Expander: Iter in each tokens and expand the variables if not
					   single quoted or a heredoc delimiter. Replace the state of
					   each expanded character in the state_array by 3 (expanded)
					   or 4 (expanded and double quoted).
					   the state_array in the example above will be:
					   echo
					   '$USER'heyccodere
					   "ccodere"
					   [0][0][0][0]
					   [1][1][1][1][1][1][1][0][0][0][3][3][3][3][3][3][3]
					   [2][4][4][4][4][4][4][4][2]
					   

		2.2- Trimmer: Iter in each tokens and remove the quotes of tokens that
				do not result from expansion. To do so, it will remove the quotes
				with the state 2 or 1 in the state_array map.
				the state_array in the example above will be:
				echo
				$USERheyccodere
				ccodere
				[0][0][0][0]
				[1][1][1][1][1][0][0][0][3][3][3][3][3][3][3]
				[4][4][4][4][4][4][4]
	
		2.3- Retokenizer: Iter in each tokens and resepare the tokens like in
						  tokenizer, but at any spaces and save the empty tokens.
						  Save each token is a dynamic char **buffer, which will
						  increase its capacity if needed. At the same time, it
						  update the quoted and expanded int * arrays, which have
						  dynamic capacity too.

		2.4- Cleaner: Called only if true pipes is found(unquoted and do not 
					  result from expansion). It will iter in the tokens and
					  remove the unquoted empty tokens resulted from empty
					  variables. This is the final step and the result is
					  assigned to ms->tokens.

	3-  We check if we have a unquoted and unexpanded heredoc, if so we execute
		and fill all valid heredocs at once and save them with an unique name in our
		folder /tmp. These are deleted after the command execution, or if we
		received a SIGINT, at exit or with the command make fclean.

	4-  if all the previous step were successful, we check if the tokens contain
		at least one unquoted and unexpanded pipe. If yes, execute the pipeline
		in exec_pipes and return the exit code of the last child process.

	5-	If the tokens contains no pipes, we execute the simple command in a
		sub-shell. Both pipes and simple command proceed like the following:

		5.1-	We check if the command exist in our built-in(except echo)
				if the command exist, execute it and return SUCCESS or ERROR

		5.2-	If not found in our built-in, We create a fork in handle_child()
				and check if the tokens contains unquoted and unexpanded
				redirections or heredocs characters. If yes, we iter in the
				tokens and redirect the output/input depending of the meta
				characters. Then we recreate the tokens without these characters
				and argument(files).

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
void	execms(t_minishell *ms)
{
	welcome(ms);
	while (1)
	{
		sync_signals(ms);
		if (ms->isatty)
		{
			ms->prompt_name = get_prompt_name(ms);
			ms->input = readline(ms->prompt_name);
		}
		else
			ms->input = get_next_line(STDIN_FILENO);
		if (!ms->input)
			break ;
		else if (*(ms->input) != '\0')
		{
			ms->ret = execute_input(ms, ms->input);
			add_history(ms->input);
		}
		if (!ms->isatty)
			exit_minishell(ms, ms->ret);
		free_data(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	char		*rl_path;

	if (argc > 1)
	{
		error_msg(argv[1], "too many arguments");
		return (1);
	}
	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ft_memset(ms, 0, sizeof(ms));
	init_minishell(ms);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		ms->isatty = 0;
	else
		ms->isatty = 1;
	init_signals_interactive(ms);
	ms->env = ft_envdup(envp);
	ms->path = getcwd(NULL, 0);
	rl_path = ft_strjoin(ms->path, "/includes/readline/.inputrc");
	free(rl_path);
	execms(ms);
	exit_minishell(ms, 0);
	return (0);
}
