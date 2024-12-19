/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 11:50:11 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Expander:
	Iter in each token and check if it's expandable. If not a heredoc delimiter
	and in singles quotes, the function will begin it's job:
	if the section begin by '$' and a letter or '_', it will iterate in this
	zone until the character evaluated is not a letter, a number or a '_'. We
	keep this len for iterating in the state_array map so we continue to
	evaluate each zone correctly.
	The section is replaced by the variable value from the environment. If the
	value is NULL, or begin with a number, we replace the $VAR with a empty str.
	If '$' is followed by another '$', we just write the dollars signs until a
	'$' sign is followed by a letter, number or '?'.
	If '$' is followed by '?', we replace the '$?' by the return value of the
	last command (value of ms->ret).
*/
char	**expander(t_minishell *ms, char **tokens)
{
	char		**expanded;
	int			count;
	t_counter	c;

	count = count_tokens(tokens);
	expanded = ft_calloc(count + 1, sizeof(char *));
	ms->token.new_state_array = ft_calloc(count + 1, sizeof(int *));
	if (!expanded)
		return (NULL);
	init_counter(&c);
	while (tokens[c.k] && c.k < count)
	{
		fill_expanded_buffer(ms, &c, expanded, tokens);
		c.k++;
	}
	ms->token.new_state_array[c.i] = NULL;
	free_state_array(ms, count);
	ms->token.state_array = ms->token.new_state_array;
	expanded[c.i] = NULL;
	return (expanded);
}

void	fill_expanded_buffer(t_minishell *ms, t_counter *c, char **expanded,
		char **tokens)
{
	if (tokens[c->k])
		init_new_state_array(ms, ft_strlen(tokens[c->k]), c->k);
	if (is_heredoc_delim(ms, tokens, c->k) || !is_expandable(ms, tokens[c->k],
			c->k))
	{
		ms->token.expansion_start = 0;
		expanded[c->i] = ft_strdup(tokens[c->k]);
		fill_new_state_array(ms, ft_strlen(tokens[c->k]), c->k);
	}
	else
		expanded[c->i] = expand_token(ms, tokens[c->k], c->k);
	if (expanded)
		c->i++;
}

char	*expand_token(t_minishell *ms, char *token, int k)
{
	char	*dup;
	int		i;
	size_t	saved_len;

	if (!token)
		return (NULL);
	dup = ft_strdup(token);
	saved_len = ft_strlen(token);
	i = 0;
	ms->token.state_index = 0;
	while (dup[i] && ms->token.state_index < saved_len)
	{
		ms->token.expansion_len = 0;
		if (in_expandable_zone(ms, dup, i, k) == TRUE)
			dup = process_expansion(ms, dup, &i, k);
		else
		{
			add_to_new_state_array(ms,
				ms->token.state_array[k][ms->token.state_index], k);
			ms->token.state_index++;
			i++;
		}
	}
	return (dup);
}

char	*process_expansion(t_minishell *ms, char *dup, int *i, int k)
{
	char	*new_dup;

	if (is_variable_expansion(dup, *i) == TRUE)
	{
		new_dup = apply_var_expansion(ms, dup, i, k);
		dup = new_dup;
		ms->token.state_index += (ms->token.expansion_len + 1);
	}
	else if (is_return_code_expansion(dup, *i) == TRUE)
	{
		new_dup = can_apply_nbr_expansion(ms, dup, i, k);
		dup = new_dup;
	}
	return (dup);
}
