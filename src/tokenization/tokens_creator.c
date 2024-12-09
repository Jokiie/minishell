/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/08 22:31:05 by ccodere          ###   ########.fr       */
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
	ms->tokc = count_tokens(ms->tokens);
	return (SUCCESS);
}

/*
	Transformer : Init quoted and expanded int arrays, which save the state
	of each token (quoted or not) and (expanded or not).
	Then call the following :
	- expander
	- retokenizer
	- cleaner
	- trimmer
*/
char	**transformer(t_minishell *ms)
{
	char	**final_tokens;
	char	**dup;

	ft_fprintf(2, "pretokens:\n");
	print_debug(ms->pretokens);
	init_int_arrays(ms);
	ft_fprintf(2, "token.quoted:\n");
	print_int_array(ms->pretokens, &ms->token.quoted);
	ft_fprintf(2, "token.expanded:\n");
	print_expanded_array(ms->pretokens, &ms->token.expanded);
	ms->expanded = expander(ms, ms->pretokens);
	free_tokens_address(&ms->pretokens);
	ft_fprintf(2, "expander:\n");
	print_debug(ms->expanded);
	ms->pretokens = retokenizer(ms);
	ft_fprintf(2, "retokenizer:\n");
	print_debug(ms->pretokens);
	free_tokens_address(&ms->expanded);
	ft_fprintf(2, "token.quoted:\n");
	print_int_array(ms->pretokens, &ms->token.quoted);
	ft_fprintf(2, "token.expanded:\n");
	print_expanded_array(ms->pretokens, &ms->token.expanded);
	final_tokens = trimmer(ms, ms->pretokens);
	if (!final_tokens)
		return (NULL);
	ft_fprintf(2, "trimmer:\n");
	print_debug(final_tokens);
	free_tokens_address(&ms->pretokens);
	if (!has_type(final_tokens, &ms->token.quoted, &ms->token.expanded,
			is_pipe))
	{
		dup = ft_envdup(final_tokens);
		free_tokens(final_tokens);
		final_tokens = cleaner(ms, dup);
		free_tokens(dup);
		ft_fprintf(2, "cleaner:\n");
		print_debug(final_tokens);
	}
	if (!final_tokens || (!final_tokens[0] && ms->token.quoted[0] == 0))
	{
		free_tokens_address(&ms->expanded);
		free_tokens_address(&ms->pretokens);
		free_tokens(final_tokens);
		return (NULL);
	}
	return (final_tokens);
}

void	init_int_arrays(t_minishell *ms)
{
	init_quoted_array(ms, ms->pretokens);
	init_expanded_array(ms, ms->pretokens);
}

void	init_quoted_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	count;

	i = 0;
	k = 0;
	count = count_tokens(tokens);
	ms->token.quoted = ft_calloc(count + 1, sizeof(int));
	if (!ms->token.quoted)
		return ;
	k = 0;
	while (tokens[k] && k < count)
	{
		if (has_quotes(tokens[k])
			&& open_quotes_checker(ms, tokens[k]) == SUCCESS)
			ms->token.quoted[i] = 1;
		else
			ms->token.quoted[i] = 0;
		k++;
		i++;
	}
}

void	init_expanded_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	size;

	size = count_tokens(tokens) * count_size(tokens);
	ms->token.expanded = ft_calloc((size * size), sizeof(int));
	ms->token.tmp_array = ft_calloc((size * size), sizeof(int));
	if (!ms->token.expanded || !ms->token.tmp_array)
		return ;
	i = 0;
	k = 0;
	while (tokens[k] && k < size)
	{
		if (is_expandable(ms, tokens[k], k) == TRUE && !is_heredoc_delim(ms,
				tokens, k))
			ms->token.expanded[i] = 1;
		else
			ms->token.expanded[i] = 0;
		k++;
		i++;
	}
	ms->token.expanded[i] = 0;
}
