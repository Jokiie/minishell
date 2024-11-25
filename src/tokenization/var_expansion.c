/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:43:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 07:02:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*apply_var_expansion(t_minishell *ms, char *token_dup, int i)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, i);
	i++;
	var = var_extractor(token_dup, &i);
	after = ft_substr(token_dup, i, ft_strlen(token_dup) - i);
	new_token_dup = insert_variable_value(ms, before, var, after);
	ft_free(token_dup);
	token_dup = new_token_dup;
	i = ft_strlen(before) + ft_strlen(get_env(ms->env, var));
	ft_free(before);
	ft_free(var);
	ft_free(after);
	return (new_token_dup);
}

char	*var_extractor(char *token, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	substr = ft_substr(token, start, *i - start);
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
	ft_free(half_token);
	return (complete_token);
}
