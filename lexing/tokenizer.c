/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/03 03:08:25 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

/* MB_SIZE / PTR_SIZE = 2097152 / 8 (max args on Linux env) */
char	**tokenizer(t_minishell *ms, char *line)
{
	int	i;
	int	k;

	k = 0;
	ms->pretokens = (char **)malloc(MB_SIZE / sizeof(char *));
	if (!ms->pretokens)
		return (NULL);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		i = separe_line(ms, line, i, &k);
		while (ft_isspace(line[i]))
			i++;
	}
	ms->pretokens[k] = NULL;
	ft_print_debug(ms->pretokens);
	return (ms->pretokens);
}

int	ft_quotes_detector(t_minishell *ms, char *line, int i)
{
	if (ft_is_dquote(line[i]) && !ms->token.in_squotes)
		ms->token.in_dquotes = !ms->token.in_dquotes;
	else if (ft_is_squote(line[i]) && !ms->token.in_dquotes)
		ms->token.in_squotes = !ms->token.in_squotes;
	return (i);
}

int	ft_open_quotes_checker(t_minishell *ms, char *line)
{
	int	i;

	i = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	while (line[i])
	{
		ft_quotes_detector(ms, line, i);
		i++;
	}
	if (ms->token.in_dquotes == TRUE || ms->token.in_squotes == TRUE)
		return (ERROR);
	return (SUCCESS);
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
			else if (ft_isredirect(line[i]))
			{
				have_meta_chars = 1;
				break ;
			}
		}
		i++;
	}
	if (i > (*t).start)
	{
		(*t).end = i;
		ms->pretokens[(*k)++] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	}
	if (have_meta_chars)
		ms->pretokens[(*k)++] = meta_chars_extractor(line, &i);
	return (i);
}

char	*meta_chars_extractor(char *line, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		(*i)+=2;
	else if ((line[*i] == '>' || line[*i] == '<')
		&& (!ft_isredirect(line[*i + 1])))
		(*i)++;
	else if (line[*i] == '<' && line[*i + 1] == '>')
		(*i)++;
	else if (line[*i] == '>' && line[*i + 1] == '<')
		(*i)++;
	else if (line[*i] == '|')
		(*i)++;
	else if (line[*i] == '|' && ft_isredirect(line[*i + 1]))
		(*i)++;
	else if (ft_isredirect(line[*i]) && line[*i] == '|')
		(*i)++;
	substr = ft_substr(line, start, *i - start);
	if (!substr)
		return (NULL);
	return (substr);
}