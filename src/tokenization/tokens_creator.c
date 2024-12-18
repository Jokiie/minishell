/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/17 22:22:51 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Tokens_creator: If line is empty or contain only spaces, ms->tokens is
	set to null, and we return 0. Otherwise, We check if we have an open
	quote, if so, we return SYNTAX_ERROR and do not proceed further.
	Otherwise, We call tokenizer and transformer, then verify if we have a
	syntax error. If so, we return SYNTAX_ERROR. If no syntax error is found,
	we return SUCCESS.
*/
int	tokens_creator(t_minishell *ms, char *line)
{
	if (!line || contains_only_spaces(line) == TRUE)
	{
		ms->tokens = NULL;
		return (0);
	}
	if (open_quotes_checker(ms, line) != SUCCESS)
	{
		ft_putendl_fd("ms: syntax error near unclosed quotes", 2);
		return (SYNTAX_ERROR);
	}
	ms->pretokens = tokenizer(ms, line);
	if (!ms->pretokens || !*ms->pretokens)
	{
		ms->tokens = NULL;
		return (SUCCESS);
	}
	ms->tokens = transformer(ms);
	if (ms->tokens && check_syntax(ms) == SYNTAX_ERROR)
	{
		free_tokens_address(&ms->tokens);
		return (SYNTAX_ERROR);
	}
	if (ms->tokens && *ms->tokens)
		ms->tokc = count_tokens(ms->tokens);
	return (SUCCESS);
}

/*
	Transformer : Init quoted and expanded int arrays, which save the state
	of each token (quoted or not) and (expanded or not).
	Then call the following :
	- parser
	- expander
	- trimmer
	- retokenizer
	- cleaner
*/
char	**transformer(t_minishell *ms)
{
	char	**final_tokens;
	char	**tmp;
	int		initial_count;

	// ft_fprintf(2, "pretokens:\n");
	// print_debug(ms->pretokens);
	parser(ms, ms->pretokens);
	initial_count = count_tokens(ms->pretokens);
	init_int_arrays(ms, ms->pretokens);
	// ft_fprintf(2, "token.quoted:\n");
	// print_int_array(ms->pretokens, &ms->token.quoted);
	// ft_fprintf(2, "token.expanded:\n");
	// print_expanded_array(ms->pretokens, &ms->token.expanded);
	ms->expanded = expander(ms, ms->pretokens);
	free_tokens_address(&ms->pretokens);
	if (!ms->expanded)
		return (NULL);
	// ft_fprintf(2, "expander:\n");
	// print_debug(ms->expanded);
	// ft_fprintf(2, "After expander:\n");
	// print_state_array(ms, ms->expanded, count_tokens(ms->expanded));
	tmp = trimmer(ms, ms->expanded);
	free_tokens_address(&ms->expanded);
	// ft_fprintf(2, "trimmer:\n");
	// print_debug(tmp);
	// print_state_array(ms, tmp, count_tokens(tmp));
	// ft_fprintf(2, "token.quoted:\n");
	// print_int_array(tmp, &ms->token.quoted);
	// ft_fprintf(2, "token.expanded:\n");
	// print_expanded_array(tmp, &ms->token.expanded);
	// ft_fprintf(2, "After update state array:\n");
	// print_state_array(ms, tmp, count_tokens(tmp));
	final_tokens = retokenizer(ms, tmp);
	free_tokens_address(&tmp);
	// ft_fprintf(2, "retokenizer:\n");
	// print_debug(final_tokens);
	// ft_fprintf(2, "token.quoted:\n");
	// print_int_array(final_tokens, &ms->token.quoted);
	// ft_fprintf(2, "token.expanded:\n");
	// print_expanded_array(final_tokens, &ms->token.expanded);
	if (final_tokens && !has_type(final_tokens, &ms->token.quoted,
			&ms->token.expanded, is_pipe))
	{
		tmp = cleaner(ms, final_tokens);
		free_tokens_address(&final_tokens);
		final_tokens = tmp;
		
		// ft_fprintf(2, "cleaner:\n");
		// print_debug(final_tokens);
		// ft_fprintf(2, "token.quoted:\n");
		// print_int_array(final_tokens, &ms->token.quoted);
		// ft_fprintf(2, "token.expanded:\n");
		// print_expanded_array(final_tokens, &ms->token.expanded);
	}
	free_state_array(ms, initial_count);
	return (final_tokens);
}
