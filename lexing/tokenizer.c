/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 02:28:19 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	ft_quotes_detector(t_minishell *ms, char *str, int i)
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

int	separe_line(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

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
	ms->tokens[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	return ((*t).end);
}

/* MB_SIZE / PTR_SIZE = 2097152 / 8 (max args on Linux env) */
void	tokenizer(t_minishell *ms, char *line, int k)
{
	int	i;
	int	nbr_of_ptrs;

	nbr_of_ptrs = MB_SIZE / PTR_SIZE;
	ms->tokens = (char **)malloc(sizeof(char *) * nbr_of_ptrs);
	if (!ms->tokens)
		return ;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		i = separe_line(ms, line, i, k);
		k++;
	}
	ms->tokens[k] = NULL;
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

int	ft_create_tokens(t_minishell *ms, char *line)
{
	int	k;

	k = 0;
	if (!line)
	{
		ms->tokens[0] = ft_strdup("");
		return (FAIL);
	}
	if (ft_open_quotes_checker(ms, line) == ERROR)
	{
		ft_fprintf(2, "ms: open quote error\n");
		return (FAIL);
	}
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	tokenizer(ms, line, k);
	characterize_tokens(ms);
	trim_tokens(ms);
	return (SUCCESS);
}
