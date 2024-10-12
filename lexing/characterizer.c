/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characterizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 02:29:26 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	characterize_tokens(t_minishell *ms)
{
	char	*characterized;
	int		k;

	k = 0;
	while (ms->tokens[k])
	{
		characterized = characterizer(ms, ms->tokens[k]);
		if (characterized)
		{
			free(ms->tokens[k]);
			ms->tokens[k] = characterized;
		}
		else
		{
			free(ms->tokens[k]);
			ms->tokens[k] = NULL;
		}
		k++;
	}
}

char	*characterizer(t_minishell *ms, char *token)
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
		if (token_dup[i] == '$' && !ms->token.in_squotes)
		{
			before = ft_substr(token_dup, 0, i);
			i++;
			var = var_extractor(token_dup, &i);
			after = ft_substr(token_dup, i, ft_strlen(token_dup) - i);
			new_token_dup = insert_variable_value(before, var, after);
			free(token_dup);
			token_dup = new_token_dup;
			i = ft_strlen(before) + ft_strlen(getenv(var));
			free(before);
			free(var);
			free(after);
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
		var_value = ft_strdup("");
	half_token = ft_strjoin(before, var_value);
	complete_token = ft_strjoin(half_token, after);
	free(half_token);
	return (complete_token);
}
