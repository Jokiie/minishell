/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/24 02:38:09 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**trimmer(t_minishell *ms, char **tokens)
{
	char	**trimmed;
	int		count;
	int		k;
	int		i;

	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	trimmed = ft_calloc(count + 1, sizeof(char *));
	if (!trimmed)
        return (NULL);
	k = 0;
	i = 0;
	while (tokens[k] && k < count)
	{
		trimmed[i] = ft_toktrim(ms, tokens[k], ft_strlen(tokens[k]));
		if (!trimmed[i])
		{
			free_tokens(trimmed);
			free(trimmed);
			return (NULL);
		}
		i++;
		k++;
	}
	trimmed[i] = NULL;
	return (trimmed);
}

char	*ft_toktrim(t_minishell *ms, char *token, int len)
{
	char	*buffer;
	int		i;
	int		j;

	if (!token)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i] && i < len)
	{
		ft_quotes_detector(ms, token, i);
		if ((i < len) && ((ft_is_squote(token[i]) && !ms->token.in_dquotes)
				|| (ft_is_dquote(token[i]) && !ms->token.in_squotes)))
		{
			i++;
		}
		else
		{
			if (token[i] != '\0')
				buffer[j++] = token[i++];
			else
				break;
		}
	}
	buffer[j] = '\0';
	return (buffer);
}
