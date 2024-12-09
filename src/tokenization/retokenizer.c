/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:38:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/09 01:35:52 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Retokenizer : Iter in each tokens and resepare the tokens like
	in tokenizer, but save the empty tokens. Then we update the quoted and
	expanded arrays, so we have the state of each new tokens.
*/
static void	init_retokenizer(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

char	**retokenizer(t_minishell *ms)
{
	int	i;
	int	j;
	int	k;
	int	size;

	if (!ms->expanded || !*ms->expanded)
		return (NULL);
	size = count_tokens(ms->expanded);
	ft_fprintf(2, GREEN"initializing retokenizer\n"RESET);
	init_retokenizer(&i, &j, &k);
	if (!init_dbuffer(ms, size))
		return (NULL);
	k = 0;
	while (ms->expanded[j])
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
	ms->token.db_buffer[ms->token.db_size] = NULL;
	ms->pretokens = ms->token.db_buffer;
	update_arrays(ms, k);
	return (ms->pretokens);
}

int	separe_token(t_minishell *ms, char *token, int *i, int *k)
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
		append_to_dbuffer_char(ms, tmp);
		(*k)++;
	}
	else if (ms->token.is_meta)
	{
		tmp = meta_chars_extractor(token, i);
		append_to_dbuffer_char(ms, tmp);
		(*k)++;
	}
	return (*i);
}

int	handle_empty(t_minishell *ms, int *k, int j)
{
	if (ms->token.expanded[j] == 1)
		ms->token.tmp_array[*k] = 1;
	else
		ms->token.tmp_array[*k] = 0;
	append_to_dbuffer_char(ms, "");
	(*k)++;
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
