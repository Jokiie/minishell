/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:43:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 17:33:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*apply_var_expansion(t_minishell *ms, char *token_dup, int *i, int k)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;
	char	*var_value;
	
	before = ft_substr(token_dup, 0, *i);
	ms->token.expansion_start = *i;
	(*i)++;
	var = var_extractor(ms, token_dup, i, k);
	after = ft_substr(token_dup, *i, ft_strlen(token_dup) - *i);
	var_value = get_env(ms->env, var);
	new_token_dup = insert_variable_value(before, var_value, after);
	free_ptr(token_dup);
	token_dup = new_token_dup;
	if (!var_value)
		*i = ft_strlen(before);
	else
		*i = ft_strlen(before) + ft_strlen(var_value);
	free_ptr(before);
	free_ptr(var);
	free_ptr(after);
	fill_3_new_state_array(ms, ms->token.expansion_start, ft_strlen(var_value), k);
	return (new_token_dup);
}

char	*var_extractor(t_minishell *ms, char *token, int *i, int k)
{
	char	*substr;
	int		start;
	int		index;

	index = ms->token.state_index;
	start = *i;
	(void)k;
	if ((ft_isalpha(token[*i]) || token[*i] == '_'))
	{
		while (token[*i] && token[*i] != '$' && (ft_isalnum(token[*i]) || token[*i] == '_'))
		{
			index++;
			(*i)++;
		}
		substr = ft_substr(token, start, *i - start);
	}
	else
	{
		(*i)++;
		substr = ft_strdup("");
	}
	ms->token.expansion_len = (*i - start);
	return (substr);
}

char	*insert_variable_value(char *before, char *var, char *after)
{
	char	*half_token;
	char	*complete_token;

	if (!var)
		var = "";
	half_token = ft_strjoin(before, var);
	complete_token = ft_strjoin(half_token, after);
	free_ptr(half_token);
	return (complete_token);
}
