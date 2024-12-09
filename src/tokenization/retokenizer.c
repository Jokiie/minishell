/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:38:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/08 22:34:25 by ccodere          ###   ########.fr       */
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
	int	i;
	int	k;
	int	j;
	int	size;

	size = count_tokens(ms->expanded) * count_size(ms->expanded);
	ms->pretokens = ft_calloc((size + 1), sizeof(char *));
	j = 0;
	k = 0;
	i = 0;
	while (ms->expanded[j] && k < size)
	{
		if (!ms->expanded[j][0])
			j = handle_empty(ms, &k, j);
		else
		{
			handle_non_empty(ms, &i, &k, j);
			j++;
			i = 0;
		}
	}
	ms->pretokens[k] = NULL;
	update_arrays(ms, k);
	return (ms->pretokens);
}

int	separe_token(t_minishell *ms, char *token, int *i, int *k)
{
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
		ms->pretokens[(*k)++] = ft_substr(token, ms->token.start,
				ms->token.size);
	else if (ms->token.is_meta)
		ms->pretokens[(*k)++] = meta_chars_extractor(token, i);
	return (*i);
}

int	handle_empty(t_minishell *ms, int *k, int j)
{
	if (ms->token.expanded[j] == 1)
	{
		ms->pretokens[*k] = ft_strdup("");
		ms->token.tmp_array[*k] = 1;
		(*k)++;
	}
	else
	{
		ms->pretokens[*k] = ft_strdup("");
		ms->token.tmp_array[*k] = 0;
		(*k)++;
	}
	return (j + 1);
}

void	handle_non_empty(t_minishell *ms, int *i, int *k, int j)
{
	while (ms->expanded[j][*i])
	{
		while (ft_isspace(ms->expanded[j][*i]))
			(*i)++;
		*i = separe_token(ms, ms->expanded[j], i, k);
		while (ft_isspace(ms->expanded[j][*i]))
			(*i)++;
		ms->token.tmp_array[*k - 1] = ms->token.expanded[j];
	}
}

void	update_arrays(t_minishell *ms, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		ms->token.expanded[i] = ms->token.tmp_array[i];
		i++;
	}
	free(ms->token.tmp_array);
	free_int_array(&ms->token.quoted);
	init_quoted_array(ms, ms->pretokens);
}
