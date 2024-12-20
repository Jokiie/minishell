/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 23:51:03 by ccodere          ###   ########.fr       */
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
		free_dbuffer(ms);
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
	int		initial_size;

	parser(ms, ms->pretokens);
	initial_size = count_tokens(ms->pretokens);
	init_int_arrays(ms, ms->pretokens);
	ms->expanded = expander(ms, ms->pretokens);
	free_tokens_address(&ms->pretokens);
	if (!ms->expanded)
		return (NULL);
	tmp = trimmer(ms, ms->expanded);
	free_tokens_address(&ms->expanded);
	final_tokens = retokenizer(ms, tmp, initial_size);
	free_tokens_address(&tmp);
	if (final_tokens && !has_type(final_tokens, &ms->token.quoted,
			&ms->token.expanded, is_pipe))
	{
		cleaner(ms, ms->token.db_buffer);
	}
	free_state_array(ms, initial_size);
	return (final_tokens);
}
