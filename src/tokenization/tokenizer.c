/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 12:25:30 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Tokenizer:
	Separe the line in tokens when we find an unquoted space or
	a meta character. Return NULL if the line is empty.
*/
char	**tokenizer(t_minishell *ms, char *line)
{
	int	i;
	int	k;
	int	count;

	k = 0;
	if (!line)
		return (NULL);
	count = ft_strlen(line);
	ms->pretokens = ft_calloc((count + 1), sizeof(char *));
	if (!ms->pretokens)
		return (NULL);
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		i = separe_line(ms, line, i, &k);
		while (ft_isspace(line[i]))
			i++;
	}
	ms->pretokens[k] = NULL;
	return (ms->pretokens);
}

int	separe_line(t_minishell *ms, char *line, int i, int *k)
{
	ms->token.is_meta = FALSE;
	ms->token.start = i;
	while (line[i])
	{
		quotes_detector(ms, line, i);
		if (is_space_or_meta(ms, line, &i))
			break ;
		i++;
	}
	ms->token.end = i;
	ms->token.size = (ms->token.end - ms->token.start);
	if (i > ms->token.start)
		ms->pretokens[(*k)++] = ft_substr(line, ms->token.start,
				ms->token.size);
	else if (ms->token.is_meta)
		ms->pretokens[(*k)++] = meta_chars_extractor(line, &i);
	return (i);
}

t_bool	is_space_or_meta(t_minishell *ms, char *token, int *i)
{
	if (!ms->token.in_dquotes && !ms->token.in_squotes)
	{
		if (ft_isspace(token[*i]) && !ms->token.in_dquotes
			&& !ms->token.in_squotes)
			return (TRUE);
		else if (ft_ismeta_chars(token[*i]) && !ms->token.in_dquotes
			&& !ms->token.in_squotes)
		{
			ms->token.is_meta = TRUE;
			return (TRUE);
		}
	}
	return (FALSE);
}

char	*meta_chars_extractor(char *line, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		(*i) += 2;
	else if (ft_ismeta_chars(line[*i]) && !ft_ismeta_chars(line[*i + 1]))
		(*i)++;
	else if (ft_ismeta_chars(line[*i]) && ft_ismeta_chars(line[*i + 1]))
		(*i)++;
	substr = ft_substr(line, start, *i - start);
	if (!substr)
		return (NULL);
	return (substr);
}
