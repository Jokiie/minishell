/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characterizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 14:02:27 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

/*
	FOr each token, iter in it to find a '$' and replace the variable if
	applicable. Replace the $VAR with a empty str if var do not exist. if '$'
	is followed by another '$', just write the dollars signs, until a '$' sign
	is followed by a letter, number, undercase or '?'. In this case, replace
	the var by the value returned while retrieving this value.
*/
char	**characterizer(t_minishell *ms, char **tokens)
{
	char	*characterized;
	int		k;

	k = 0;
	while (tokens[k] && k < ms->tokc)
	{
		characterized = characterize_token(ms, tokens[k], 0);
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

char	*characterize_token(t_minishell *ms, char *token, int i)
{
	char	*token_dup;
	char	*new_token_dup;

	token_dup = ft_strdup(token);
	while (token_dup[i])
	{
		ft_quotes_detector(ms, token_dup, i);
		if (token_dup[i] == '$' && !ms->token.in_squotes
			&& (ft_isalnum(token_dup[i + 1]) || token_dup[i + 1] == '_'))
		{
			new_token_dup = apply_var_expansion(token_dup, i);
			token_dup = new_token_dup;
		}
		else if ((token_dup[i] == '$' && token_dup[i + 1] == '?')
			&& !ms->token.in_squotes)
		{
			new_token_dup = apply_return_value(ms, token_dup, i);
			token_dup = new_token_dup;
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
