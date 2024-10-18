/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:43:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 02:50:27 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*apply_var_expansion(char *token_dup, int i)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, i);
	i++;
	var = var_extractor(token_dup, &i);
	after = ft_substr(token_dup, i, ft_strlen(token_dup) - i);
	new_token_dup = insert_variable_value(before, var, after);
	ft_free(token_dup);
	token_dup = new_token_dup;
	i = ft_strlen(before) + ft_strlen(getenv(var));
	ft_free(before);
	ft_free(var);
	ft_free(after);
	return (new_token_dup);
}

char	*ret_var_extractor(char *token, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	(*i)++;
	substr = ft_substr(token, start, *i - start);
	return (substr);
}
char	*insert_return_value(t_minishell *ms, char *before, char *after)
{
	char	*var_value;
	char	*half_token;
	char	*complete_token;

	var_value = ft_itoa(ms->ret);
	if (!var_value)
		var_value = "";
	half_token = ft_strjoin(before, var_value);
	complete_token = ft_strjoin(half_token, after);
	ft_free(half_token);
	return (complete_token);
}

char	*apply_return_value(t_minishell *ms, char *token_dup, int i)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, i);
	i++;
	var = ret_var_extractor(token_dup, &i);
	after = ft_substr(token_dup, i, ft_strlen(token_dup) - i);
	new_token_dup = insert_return_value(ms, before, after);
	ft_free(token_dup);
	token_dup = new_token_dup;
	i = ft_strlen(before) + ft_strlen(getenv(var));
	ft_free(before);
	ft_free(var);
	ft_free(after);
	return (new_token_dup);
}
