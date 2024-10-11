/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/11 13:35:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int		ft_quotes_detector(t_minishell *ms, char *str, int i)
{
	if (ft_isquotes(str[i]))
	{
		if (ft_is_dquote(str[i]) && !ms->token.in_squotes)
			ms->token.in_dquotes = !ms->token.in_dquotes;
		else if (ft_is_squote(str[i]) && !ms->token.in_dquotes)
			ms->token.in_squotes = !ms->token.in_squotes;
		return (i + 1);
	}
	return (i);
}
char	*ft_toktrim(t_minishell *ms, char *str, int len)
{
	char	*buffer;
	int		i;
	int		j;
	
	if (!str)
		return (NULL);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	while (str[i] && j < len)
	{
		i = ft_quotes_detector(ms, str, i);
		if ((ms->token.in_dquotes && ft_is_dquote(str[i]))
			|| (ms->token.in_squotes && ft_is_squote(str[i])))
			i++;
		else if ((ms->token.in_dquotes && !ft_is_dquote(str[i]))
			|| (ms->token.in_squotes && !ft_is_squote(str[i])))
			buffer[j++] = str[i];
		else if (!ft_isquotes(str[i]))
			buffer[j++] = str[i];
		i++;
	}
	buffer[j] = '\0';
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	return (buffer);
}

void	trim_tokens(t_minishell *ms)
{
	char *trimmed;
	int k;
	
	k = 0;
	while (ms->tokens[k])
	{
		trimmed = ft_toktrim(ms, ms->tokens[k], ft_strlen(ms->tokens[k]));
		if (trimmed)
		{
			free(ms->tokens[k]);
			ms->tokens[k] = trimmed;
		}
		k++;
	}
}
