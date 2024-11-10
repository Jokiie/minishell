/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characterizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/10 00:03:27 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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
	char	*tmp;
	int		k;

	k = 0;
	while (tokens[k] && k < ms->tokc)
	{
		tmp = tokens[k];
		characterized = characterize_token(ms, tokens[k], 0);
		if (characterized)
		{
			tokens[k] = characterized;
			ft_free(tmp);
		}
		else
			ft_free(tmp);
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
		else if (token_dup[i] == '$' && !ms->token.in_squotes
			&& token_dup[i + 1] == '?')
		{
			new_token_dup = apply_nbr_expansion(ms, token_dup, i);
			token_dup = new_token_dup;
		}
		else
			i++;
	}
	return (token_dup);
}

char	*apply_nbr_expansion(t_minishell *ms, char *token_dup, int i)
{
	char	*new_token_dup;

	new_token_dup = NULL;
	if ((token_dup[i] == '$' && token_dup[i + 1] == '?')
		&& !ms->token.in_squotes)
		new_token_dup = apply_nbr_value(token_dup, i, ms->ret);
	return (new_token_dup);
}
