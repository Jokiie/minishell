/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 21:50:05 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	**transformer(t_minishell *ms)
{
	char	**final_tokens;
	char	**dup;

	//ft_fprintf(2, "pretokens:\n");
	//print_debug(ms->pretokens);
	
	init_int_arrays(ms);
	
	//ft_fprintf(2, "token.quoted:\n");
	//print_int_array(ms->pretokens, &ms->token.quoted);
	//ft_fprintf(2, "token.expanded:\n");
	//print_expanded_array(ms->pretokens, &ms->token.expanded);
	
	ms->expanded = expander(ms, ms->pretokens);
	free_tokens_address(&ms->pretokens);
	
	//ft_fprintf(2, "expander:\n");
	//print_debug(ms->expanded);
	ms->pretokens = separator(ms, ms->expanded);
	
	//ft_fprintf(2, "separator:\n");
	//print_debug(ms->pretokens);
	
	free_tokens_address(&ms->expanded);
	
	free_int_array(&ms->token.quoted);
	fill_quoted_arr(ms, ms->pretokens);

	//ft_fprintf(2, "token.quoted:\n");
	//print_int_array(ms->pretokens, &ms->token.quoted);
	//ft_fprintf(2, "token.expanded:\n");
	//print_expanded_array(ms->pretokens, &ms->token.expanded);
	
	final_tokens = trimmer(ms, ms->pretokens);
	if (!final_tokens)
		return (NULL);
	
	//ft_fprintf(2, "trimmer:\n");
	//print_debug(final_tokens);

	free_tokens_address(&ms->pretokens);
	
	if (!has_type(final_tokens, &ms->token.quoted, &ms->token.expanded, is_pipe))
	{
		dup = ft_envdup(final_tokens);
		free_tokens(final_tokens);
		final_tokens = cleaner(ms, dup);
		free_tokens(dup);
		
		//ft_fprintf(2, "cleaner:\n");
		//print_debug(final_tokens);
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
	fill_quoted_arr(ms, ms->pretokens);
	init_expanded_array(ms, ms->pretokens);
}

void	fill_quoted_arr(t_minishell *ms, char **tokens)
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
