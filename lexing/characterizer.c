/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characterizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/13 03:48:51 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	**characterizer(t_minishell *ms, char **tokens)
{
	char	*characterized;
	int		k;

	k = 0;
	while (tokens[k] && k < ms->tokc)
	{
		characterized = characterize_token(ms, tokens[k]);
		if (characterized)
		{
			ft_free(tokens[k]);
			tokens[k] = characterized;
		}
		else
			ft_free(tokens[k]);
		k++;
	}
	return (tokens);
}

char	*characterize_token(t_minishell *ms, char *token)
{
	int		i;
	char	*var;
	char	*before;
	char	*after;
	char	*token_dup;
	char	*new_token_dup;

	token_dup = ft_strdup(token);
	i = 0;
	while (token_dup[i])
	{
		ft_quotes_detector(ms, token_dup, i);
		if (token_dup[i] == '$' && !ms->token.in_squotes
			&& (ft_isalnum(token_dup[i + 1]) || token_dup[i + 1] == '_'))
		{
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
		}
		else
			i++;
	}
	return (token_dup);
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

char	*insert_variable_value(char *before, char *var, char *after)
{
	char	*var_value;
	char	*half_token;
	char	*complete_token;

	var_value = getenv(var);
	if (!var_value)
		var_value = "";
	half_token = ft_strjoin(before, var_value);
	complete_token = ft_strjoin(half_token, after);
	ft_free(half_token);
	return (complete_token);
}
