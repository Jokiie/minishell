/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/09 01:17:24 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

char	**trimmer(t_minishell *ms, char **tokens)
{
	char	*trimmed;
	int		k;

	k = 0;
	if (!tokens || !*tokens)
		return (NULL);
	while (tokens[k])
	{
		trimmed = ft_toktrim(ms, tokens[k], ft_strlen(tokens[k]));
		if (trimmed)
		{
			ft_free(tokens[k]);
			tokens[k] = trimmed;
		}
		else
			ft_free(tokens[k]);
		k++;
	}
	return (tokens);
}

t_bool	have_heredoc(char *heredoc, char *delim)
{
	if (!has_quotes(heredoc) && is_heredoc(heredoc))
	{
		if (has_quotes(delim))
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

char	*ft_toktrim(t_minishell *ms, char *token, int len)
{
	char	*buffer;
	int		i;
	int		j;

	if (!token)
		return (NULL);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && j < len)
	{
		ft_quotes_detector(ms, token, i);
		if ((i < len) && ((ft_is_squote(token[i]) && !ms->token.in_dquotes)
				|| (ft_is_dquote(token[i]) && !ms->token.in_squotes)))
			i++;
		else
		{
			if (i < len)
				buffer[j++] = token[i++];
		}
	}
	buffer[j] = '\0';
	return (buffer);
}
