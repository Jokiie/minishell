/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/11 01:28:11 by ccodere          ###   ########.fr       */
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
	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	trimmed = ft_calloc(count + 1, sizeof(char *));
	if (!trimmed)
		return (NULL);
	while (tokens[k])
	{
		trimmed[i] = ft_toktrim(ms, tokens[k], ft_strlen(tokens[k]), k);
		if (trimmed[i])
			i++;
		k++;
	}
	trimmed[i] = NULL;
	return (trimmed);
}

char	*ft_toktrim(t_minishell *ms, char *token, int len, int cexpindex)
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
	while (i < len)
	{
		quotes_detector(ms, token, i);
		if ((i < len) && ((ft_is_squote(token[i]) && !ms->token.in_dquotes)
				|| (ft_is_dquote(token[i]) && !ms->token.in_squotes))
				&& ms->token.cexpanded[cexpindex][i] != 1)
			i++;
		else if (i < len)
			buffer[j++] = token[i++];
	}
	buffer[j] = '\0';
	return (buffer);
}
