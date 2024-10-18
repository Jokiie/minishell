/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 14:03:50 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

/* MB_SIZE / PTR_SIZE = 2097152 / 8 (max args on Linux env) */
char	**tokenizer(t_minishell *ms, char *line)
{
	int	nbr_of_ptrs;
	int	i;
	int	k;

	k = 0;
	nbr_of_ptrs = MB_SIZE / PTR_SIZE;
	ms->pretokens = (char **)malloc(sizeof(char *) * nbr_of_ptrs);
	if (!ms->pretokens)
		return (NULL);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		i = separe_line(ms, line, i, k);
		while (ft_isspace(line[i]))
			i++;
		k++;
	}
	ms->pretokens[k] = NULL;
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
	while (line[i])
	{
		ft_quotes_detector(ms, line, i);
		i++;
	}
	if (ms->token.in_dquotes == TRUE || ms->token.in_squotes == TRUE)
		return (ERROR);
	return (SUCCESS);
}

int	separe_line(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;

	t = &(ms->token);
	(*t).start = i;
	while (line[i])
	{
		ft_quotes_detector(ms, line, i);
		if (!(*t).in_dquotes && !(*t).in_squotes)
		{
			if (ft_isspace(line[i]))
				break ;
		}
		i++;
	}
	(*t).end = i;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	if (!substr)
		ms->pretokens[k] = NULL;
	else
		ms->pretokens[k] = substr;
	return (i);
}
