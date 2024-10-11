/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/11 11:58:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	separe_line(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	
	t = &(ms->token);
	(*t).start = i;
	while (ft_isquotes(line[i]))
	{
		i++;
		(*t).in_quotes = !(*t).in_quotes;
	}
	while (line[i])
	{	
		if (ft_isquotes(line[i]))
			(*t).in_quotes = !(*t).in_quotes;
		if (((i > 0 && ft_isquotes(line[i - 1])) && ft_isspace(line[i]))
			|| (ft_isquotes(line[i]) && line[i + 1] == '\0')
			|| (!(*t).in_quotes && ft_isspace(line[i])))
		{
			if (ft_isquotes(line[i]))
			 	(*t).in_quotes = !(*t).in_quotes;
			break ;
		}
		i++;
	}
	if (line[i + 1] == '\0' || ft_isspace(line[i + 1]))
		(*t).end = i + 1;
	else if (line[i] == '\0' || ft_isspace(line[i]) || ft_isquotes(line[i]))
		(*t).end = i;
	ms->tokens[k] =  ft_substr(line, (*t).start, ((*t).end - (*t).start));
	return ((*t).end);
}

void	tokenizer(t_minishell *ms, char *line, int k)
{
	int	i;
	int	nbr_of_ptrs;
	
	nbr_of_ptrs = MB_SIZE / PTR_SIZE; // 2097152 / 8 (max args on Linux env)
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

int	ft_create_tokens(t_minishell *ms, char *line)
{
	int	k;
	
	k = 0;
	if (!line)
	{
		ms->tokens[0] = ft_strdup("");
		return (FAIL);
	}
	if (ft_charcount(line, '"') % 2 != 0 || ft_charcount(line, '\'') % 2 != 0)
	{
		ft_fprintf(2, "ms: open quote error\n");
		return (FAIL);
	}
	tokenizer(ms, line, k); // make ms->tokens // need to rework
	characterize_tokens(ms);
	trim_tokens(ms); // need to handle echo 'one "two" three'four"five"six"seven 'eight' nine"ten
	return (SUCCESS);
}
