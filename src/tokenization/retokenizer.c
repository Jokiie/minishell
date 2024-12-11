/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:38:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/11 02:04:49 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Retokenizer : Iter in each tokens and resepare the tokens like
	in tokenizer, but save the empty tokens. Then we update the quoted and
	expanded arrays, so we have the state of each new tokens.
*/

char	**retokenizer(t_minishell *ms)
{
	int	j;
	size_t	size;
	int		*saved_expanded;
	
	if (!ms->expanded || !*ms->expanded)
		return (NULL);
	size = count_tokens(ms->expanded);
	if (!init_dbuffer(ms, size))
	{
		free_tokens(ms->token.db_buffer);
		return (NULL);
	}
	j = 0;
	saved_expanded = ms->token.expanded;
	while (ms->expanded[j])
	{
		if (!ms->expanded[j][0])
			handle_empty(ms, saved_expanded[j]);
		else if (ms->expanded[j][0] && ms->token.expanded[j] == 1)
			handle_non_empty(ms, j);
		else
			append_to_dbuffer_char(ms, ft_strdup(ms->expanded[j]), 0);
		j++;
	}
	ms->token.db_buffer[ms->token.db_size] = NULL;
	update_arrays(ms, ms->token.db_size);
	return (ms->token.db_buffer);
}

int	separe_token(t_minishell *ms, char *token, int *i)
{
	char	*tmp;

	ms->token.is_meta = FALSE;
	ms->token.start = *i;
	while (token[*i])
	{
		quotes_detector(ms, token, *i);
		if (is_space_or_meta(ms, token, i) == TRUE)
			break ;
		(*i)++;
	}
	ms->token.end = *i;
	ms->token.size = (ms->token.end - ms->token.start);
	if (*i > ms->token.start)
	{
		tmp = ft_substr(token, ms->token.start, ms->token.size);
		append_to_dbuffer_char(ms, tmp, 1);
	}
	else if (ms->token.is_meta)
	{
		tmp = meta_chars_extractor(token, i);
		append_to_dbuffer_char(ms, tmp, 1);
	}
	return (*i);
}

void	handle_empty(t_minishell *ms, int expanded)
{
	if (expanded == 1)
		append_to_dbuffer_char(ms, ft_strdup(""), 1);
	else if (expanded == 0)
		append_to_dbuffer_char(ms, ft_strdup(""), 0);
}

void	handle_non_empty(t_minishell *ms, int j)
{
	int	i;

	i = 0;
	while (ms->expanded[j][i])
	{
		while (ft_isspace(ms->expanded[j][i]))
			i++;
		i = separe_token(ms, ms->expanded[j], &i);
		while (ft_isspace(ms->expanded[j][i]))
			i++;
	}
}