/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/23 12:35:12 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**tokenizer(t_minishell *ms, char *line)
{
	int	i;
	int	k;
	int	count;
	
	k = 0;
	if (!line)
	{
		ms->pretokens = NULL;
		return (NULL);
	}
	count = count_words(line);
	ms->pretokens = ft_calloc((count * 10), sizeof(char *));
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
	t_token	*t;
	int		have_meta_chars;

	have_meta_chars = 0;
	t = &(ms->token);
	(*t).start = i;
	while (line[i])
	{
		ft_quotes_detector(ms, line, i);
		if (!(*t).in_dquotes && !(*t).in_squotes)
		{
			if (ft_isspace(line[i]))
				break ;
			else if (ft_ismeta_chars(line[i]))
			{
				have_meta_chars = 1;
				break ;
			}
		}
		i++;
	}
	(*t).end = i;
	if (i > (*t).start)
		ms->pretokens[(*k)++] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	else if (have_meta_chars)
		ms->pretokens[(*k)++] = meta_chars_extractor(line, &i);
	return (i);
}

char	*meta_chars_extractor(char *line, int *i)
{
	char *substr;
	int start;

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

int	count_words(char const *line)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!line[i])
		return (1);
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i])
		{
			count++;
			while (line[i] && !ft_isspace(line[i]))
				i++;
		}
	}
	return (count);
}
