/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:43:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/10 17:56:14 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*apply_var_expansion(t_minishell *ms, char *token_dup, int *i,
		int cexpindex)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;
	char	*var_value;

	before = ft_substr(token_dup, 0, *i);
	(*i)++;
	ms->token.cexp_start = *i;
	var = var_extractor(token_dup, i);
	after = ft_substr(token_dup, *i, ft_strlen(token_dup) - *i);
	new_token_dup = insert_variable_value(ms, before, var, after);
	free_ptr(token_dup);
	token_dup = new_token_dup;
	var_value = get_env(ms->env, var);
	if (!var_value)
		*i = ft_strlen(before);
	else
		*i = ft_strlen(before) + ft_strlen(var_value);
	fill_1_cexpanded(ms, ms->token.cexp_start, ft_strlen(var_value), cexpindex);
	free_ptr(before);
	free_ptr(var);
	free_ptr(after);
	return (new_token_dup);
}

char	*var_extractor(char *token, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	if (ft_isalpha(token[*i]) || token[*i] == '_')
	{
		while (token[*i] && token[*i] != '$' && (ft_isalnum(token[*i])
				|| token[*i] == '_'))
			(*i)++;
		substr = ft_substr(token, start, *i - start);
	}
	else
	{
		(*i)++;
		return (ft_strdup(""));
	}
	return (substr);
}

char	*insert_variable_value(t_minishell *ms, char *before, char *var,
		char *after)
{
	char	*var_value;
	char	*half_token;
	char	*complete_token;

	var_value = get_env(ms->env, var);
	if (!var_value)
		var_value = "";
	half_token = ft_strjoin(before, var_value);
	complete_token = ft_strjoin(half_token, after);
	free_ptr(half_token);
	return (complete_token);
}

int	get_size_without_space(t_minishell *ms, char *str)
{
	int i;
	int count;
	int initial_size;
	
	i = 0;
	count = 0;
	if (!str)
		return (1);
	initial_size = ft_strlen(str);
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	while (str[i])
	{
		quotes_detector(ms, str, i);
		if (!ms->token.in_squotes && !ms->token.in_dquotes && ft_isspace(str[i]))
			count++;
		i++;
	}
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	return (initial_size - count);
	
}