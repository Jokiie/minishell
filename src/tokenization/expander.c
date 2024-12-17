/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/17 01:34:34 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Expander:
	Iter in each token and search a '$' character. If not a heredoc delimiter
	and is not single quoted, replace the variable by its value in the
	environment. If the value is NULL, replace the $VAR with a empty str. If '$'
	is followed by another '$', we just write the dollars signs until a '$' sign
	is followed by a letter, number or '?'. If this is the case, we replace the
	variable by the value of the environment variable or the return value of
	the last command if it's a '?'.
*/

char	**expander(t_minishell *ms, char **tokens)
{
	char	**expanded;
	int		count;
	int		k;
	int		i;

	k = 0;
	i = 0;
	count = count_tokens(tokens);
	expanded = ft_calloc(count + 1, sizeof(char *));
	ms->token.new_state_array = ft_calloc(count + 1, sizeof(int *));
	if (!expanded)
		return (NULL);
	while (tokens[k] && k < count)
	{
		if (tokens[k])
			init_new_state_array(ms, ft_strlen(tokens[k]), k);
		if (is_heredoc_delim(ms, tokens, k) || !is_expandable(ms, tokens[k], k))
		{
			ms->token.expansion_start = 0;
			expanded[i] = ft_strdup(tokens[k]);
			fill_new_state_array(ms, ft_strlen(tokens[k]), k);
		}
		else
			expanded[i] = expand_token(ms, tokens[k], k);
		if (expanded)
			i++;
		k++;
	}
    ms->token.new_state_array[i] = NULL;
	free_state_array(ms, count);
	ms->token.state_array = ms->token.new_state_array;
	expanded[i] = NULL;
	return (expanded);
}

char	*expand_token(t_minishell *ms, char *token, int k)
{
	char	*dup;
	char	*new_dup;
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
        if (ms->token.state_index >= saved_len)
            break;
        ms->token.expansion_len = 0;
		if (in_expandable_zone(ms, dup, i, k) == TRUE)
        {
			if (is_variable_expansion(dup, i) == TRUE)
			{
				new_dup = apply_var_expansion(ms, dup, &i, k);
				dup = new_dup;
                ms->token.state_index += (ms->token.expansion_len + 1);
            }
		    else if (is_return_code_expansion(dup, i) == TRUE)
		    {
			    new_dup = can_apply_nbr_expansion(ms, dup, &i, k);
			    dup = new_dup;
            }
        }
		else
		{
			add_to_new_state_array(ms, ms->token.state_array[k][ms->token.state_index], k);
			ms->token.state_index++;
			i++;
		}
	}
	return (dup);
}

t_bool	in_expandable_zone(t_minishell *ms, char *token, int i, int k)
{
	if (token[i] && token[i + 1] && ms->token.state_array[k][ms->token.state_index] != 1
        && ms->token.state_array[k][ms->token.state_index + 1] != 1)
	{
		if (token[i] == '$' && (ft_isalnum(token[i + 1]) || token[i + 1] == '_' || token[i + 1] == '?'))
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

