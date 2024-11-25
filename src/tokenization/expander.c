/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 06:57:11 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Iter in each token and search an unquoted '$' and replace the variable by
	its value in the environment. If the value is NULL, replace the $VAR with
	a empty str. If '$' is followed by another '$', we just write the dollars
	signs until a '$' sign is followed by a letter, number or '?'. In this case,
	we replace the variable by the value of the environment variable or the
	return value of the last command if it's a '?'.
*/
char	**expander(t_minishell *ms, char **tokens)
{
	char	**expanded;
	int		count;
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (!tokens || !*tokens)
		return (NULL);
	count = count_tokens(tokens);
	expanded = ft_calloc(count + 1, sizeof(char *));
	if (!expanded)
		return (NULL);
	while (tokens[k] && k < count)
	{
		expanded[i] = expand_token(ms, tokens[k], 0);
		if (expanded)
			i++;
		k++;
	}
	expanded[i] = NULL;
	return (expanded);
}

char	*expand_token(t_minishell *ms, char *token, int i)
{
	char	*dup;
	char	*new_dup;

	dup = ft_strdup(token);
	while (dup[i])
	{
		quotes_detector(ms, dup, i);
		if (dup[i] == '$' && !ms->token.in_squotes && (ft_isalnum(dup[i + 1])
				|| dup[i + 1] == '_'))
		{
			new_dup = apply_var_expansion(ms, dup, i);
			dup = new_dup;
		}
		else if (dup[i] == '$' && !ms->token.in_squotes && dup[i + 1] == '?')
		{
			new_dup = apply_nbr_expansion(ms, dup, i);
			dup = new_dup;
		}
		else
			i++;
	}
	return (dup);
}
