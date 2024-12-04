/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:43:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/03 18:43:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*apply_var_expansion(t_minishell *ms, char *token_dup, int *i)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, *i);
	(*i)++;
	var = var_extractor(token_dup, i);
	after = ft_substr(token_dup, *i, ft_strlen(token_dup) - *i);
	new_token_dup = insert_variable_value(ms, before, var, after);
	free_ptr(token_dup);
	token_dup = new_token_dup;
	*i = ft_strlen(before) + ft_strlen(get_env(ms->env, var));
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
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
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
