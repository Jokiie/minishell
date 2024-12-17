/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:38:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/17 01:51:20 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Retokenizer : Iter in each tokens and resepare the tokens like
	in tokenizer, but save the empty tokens. Then we update the quoted and
	expanded arrays, so we have the state of each new tokens.
*/

char	**retokenizer(t_minishell *ms, char **tokens)
{
	size_t		j;
	size_t		size;
	int			*saved_expanded;
	int			*saved_quoted;
	
	if (!tokens || !*tokens)
		return (NULL);
	size = count_tokens(tokens);
	if (!init_dbuffer(ms, size * 2))
		return (NULL);
	saved_expanded = ft_calloc(size, sizeof(int));
	ft_memcpy(saved_expanded, ms->token.expanded, sizeof(int) * size);
	saved_quoted = ft_calloc(size, sizeof(int));
	ft_memcpy(saved_quoted, ms->token.quoted, sizeof(int) * size);
	j = 0;
	ms->token.state_index = 0;
	while (tokens[j] && j < size)
	{
		ms->token.expansion_state = saved_expanded[j];
		ms->token.quoted_state = saved_quoted[j];
		if (!tokens[j][0] && j != (size - 1))
			append_to_dbuffer_char(ms, ft_strdup(""));
		if (saved_expanded[j] == 1)
			handle_non_empty(ms, tokens, j);
		else
			append_to_dbuffer_char(ms, ft_strdup(tokens[j]));
		j++;
	}
	ms->token.db_buffer[ms->token.db_size] = NULL;
	free_int_array(&saved_expanded);
	free_int_array(&saved_quoted);
	return (ms->token.db_buffer);
}

t_bool	is_space_or_meta2(t_minishell *ms, char *token, int *i, int k)
{
	if (ft_isspace(token[*i]) && !is_quoted_char(ms, i, k))
	{
		return (TRUE);
	}
	else if (ft_ismeta_chars(token[*i]) && ms->token.state_array[k][*i] == 0)
	{
		ms->token.is_meta = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

int separe_token(t_minishell *ms, char *token, int *i, int k)
{
    char    *tmp;

    ms->token.is_meta = FALSE;
    ms->token.start = *i;
    while (token[*i])
    {
        quotes_detector3(ms, token, *i, k);
        if (is_space_or_meta2(ms, token, i, k) == TRUE)
            break;
        (*i)++;
    }
    ms->token.end = *i;
    ms->token.size = (ms->token.end - ms->token.start);
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
    else if (*i > ms->token.start && ms->token.is_meta)
    {
        tmp = ft_calloc(ms->token.size + 1, sizeof(char));
		ft_memcpy(tmp, token + ms->token.start, ms->token.size);
		ms->token.is_meta = FALSE;
    }
    return (*i);
}

void	handle_non_empty(t_minishell *ms, char **tokens, int j)
{
	int	i;

	if (!tokens[j])
		return ;
	i = 0;
	while (tokens[j][i])
	{
		while (ft_isspace(tokens[j][i]) && !is_quoted_char(ms, &i, j))
			i++;
		i = separe_token(ms, tokens[j], &i, j);
		while (ft_isspace(tokens[j][i]) && !is_quoted_char(ms, &i, j))
			i++;
	}
}
