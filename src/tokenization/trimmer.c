/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/09 01:48:34 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Trimmer:
	Iter in each tokens and remove the quotes of tokens that do not result from
	expansion. This is the final step and the result is assigned to ms->tokens.
*/
char	**trimmer(t_minishell *ms, char **tokens)
{
	char	**trimmed;
	int		count;
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (!tokens || !*tokens)
		return (NULL);
	count = count_tokens(tokens);
	trimmed = ft_calloc(count + 1, sizeof(char *));
	if (!trimmed)
		return (NULL);
	while (tokens[k] && k < count)
	{
		trimmed[i] = trim_or_dup(ms, tokens, k);
		if (trimmed[i])
			i++;
		k++;
	}
	trimmed[i] = NULL;
	return (trimmed);
}

char	*trim_or_dup(t_minishell *ms, char **tokens, int k)
{
	if (ms->token.expanded[k] == 1)
		return (ft_strdup(tokens[k]));
	return (ft_toktrim(ms, tokens[k], ft_strlen(tokens[k])));
}

char	*ft_toktrim(t_minishell *ms, char *token, int len)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!token)
		return (NULL);
	buffer = ft_calloc((len + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	while (i < len && j < len)
	{
		quotes_detector(ms, token, i);
		if ((i < len) && ((ft_is_squote(token[i]) && !ms->token.in_dquotes)
				|| (ft_is_dquote(token[i]) && !ms->token.in_squotes)))
			i++;
		else if (i < len)
			buffer[j++] = token[i++];
	}
	buffer[j] = '\0';
	return (buffer);
}
