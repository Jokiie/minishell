/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/16 03:55:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	ft_quotes_detector(t_minishell *ms, char *line, int i)
{
	if (ft_isquotes(line[i]))
	{
		if (ft_is_dquote(line[i]) && !ms->token.in_squotes)
			ms->token.in_dquotes = !ms->token.in_dquotes;
		else if (ft_is_squote(line[i]) && !ms->token.in_dquotes)
			ms->token.in_squotes = !ms->token.in_squotes;
		return (i + 1);
	}
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
	ms->pretokens[k] = substr;
	return (i);
}

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


int	ft_create_tokens(t_minishell *ms, char *line)
{
	char	**tmp_pretokens;
	
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.in_quotes = FALSE;
	if (!line)
	{
		ms->tokens = ft_calloc(1, sizeof(char));
		return (SUCCESS);
	}
	if (ft_open_quotes_checker(ms, line) != SUCCESS)
	{
		ft_fprintf(2, "ms: open quote error\n");
		return (ERROR);
	}
	tokenizer(ms, line);
	if (ms->pretokens)
	{
		ms->tokc = ft_count_tokens(ms->pretokens);
		tmp_pretokens = ms->pretokens;
		ms->tokens = ft_envdup(ms->pretokens);
		ms->pretokens = characterizer(ms, ms->tokens);
		ms->tokens = trimmer(ms, ms->pretokens);
		ft_free_tokens(tmp_pretokens);
		return (SUCCESS);
	}
	ft_free_tokens(ms->pretokens);
	return (FAIL);
}
