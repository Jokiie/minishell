/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 15:44:45 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (ms->token.expanded[k] == 1 && !ft_strnstr(tokens[0], "export\0", 7)
			&& !(k > 0 && (is_heredoc(tokens[k - 1]) && ms->token.quoted[k - 1] == 0) && tokens[k]))
			trimmed[i] = ft_strdup(tokens[k]);
		else
			trimmed[i] = ft_toktrim(ms, tokens[k], ft_strlen(tokens[k]));
		if (trimmed[i])
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
