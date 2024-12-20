/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:38:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 23:19:01 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Retokenizer : Iter in each tokens and resepare the tokens like
	in tokenizer, but save the empty tokens. Then we update the quoted and
	expanded arrays, so we have the state of each new tokens.
*/
char	**retokenizer(t_minishell *ms, char **tokens, int initial_size)
{
	int			*saved_expanded;
	int			*saved_quoted;
	t_counter	c;

	if (!tokens || !*tokens)
		return (NULL);
	if (!init_dbuffer(ms, initial_size * 2))
		return (NULL);
	init_retokenizer(ms, &saved_expanded, &saved_quoted, initial_size);
	init_counter(&c);
	while (tokens[c.k] && c.k < initial_size)
	{
		ms->token.expansion_state = saved_expanded[c.k];
		ms->token.quoted_state = saved_quoted[c.k];
		if (!tokens[c.k][0])
			append_to_dbuffer_char(ms, ft_strdup(""));
		else
			fill_dbuffer(ms, &c, tokens, saved_expanded[c.k]);
		c.k++;
	}
	ms->token.db_buffer[ms->token.db_size] = NULL;
	free_int_array(&saved_expanded);
	free_int_array(&saved_quoted);
	return (ms->token.db_buffer);
}

void	fill_dbuffer(t_minishell *ms, t_counter *c, char **tokens,
		int saved_expanded)
{
	char	*tmp;

	if (saved_expanded == 1)
		handle_non_empty(ms, tokens, c->k);
	else if (tokens[c->k] && saved_expanded == 0)
	{
		tmp = ft_strdup(tokens[c->k]);
		append_to_dbuffer_char(ms, tmp);
	}
}

void	extract_new_token(t_minishell *ms, char *token, int *i, int k)
{
	char	*tmp;

	if (*i > ms->token.start)
	{
		tmp = ft_calloc(ms->token.size + 1, sizeof(char));
		ft_memcpy(tmp, token + ms->token.start, ms->token.size);
		if (get_quoted_state(ms, ms->token.start, ms->token.size, k) == TRUE)
			ms->token.quoted_state = 1;
		else
			ms->token.quoted_state = 0;
		append_to_dbuffer_char(ms, tmp);
	}
}

int	separe_token(t_minishell *ms, char *token, int *i, int k)
{
	ms->token.start = *i;
	while (token[*i])
	{
		quotes_detector_state(ms, token, *i, k);
		if (is_space_state(ms, token, i, k) == TRUE)
			break ;
		(*i)++;
	}
	ms->token.end = *i;
	ms->token.size = (ms->token.end - ms->token.start);
	extract_new_token(ms, token, i, k);
	return (*i);
}

void	handle_non_empty(t_minishell *ms, char **tokens, int k)
{
	int	i;

	if (!tokens[k])
		return ;
	i = 0;
	while (tokens[k][i])
	{
		while (ft_isspace(tokens[k][i]) && !is_quoted_state(ms, &i, k))
			i++;
		i = separe_token(ms, tokens[k], &i, k);
		while (ft_isspace(tokens[k][i]) && !is_quoted_state(ms, &i, k))
			i++;
	}
}
