/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 02:15:04 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 02:16:22 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_counter(t_counter *c)
{
	c->i = 0;
	c->j = 0;
	c->g = 0;
	c->k = 0;
}

t_bool	is_expandable(t_minishell *ms, char *token, int k)
{
	int		i;
	t_bool	expandable;

	expandable = FALSE;
	i = 0;
	if (!token)
		return (FALSE);
	while (token[i])
	{
		if (token[i] && ms->token.state_array[k][i] != 1 && token[i + 1]
			&& ms->token.state_array[k][i + 1] != 1)
		{
			if (token[i] == '$' && (ft_isalnum(token[i + 1]) || token[i
					+ 1] == '_' || token[i + 1] == '?'))
			{
				expandable = TRUE;
			}
		}
		i++;
	}
	if (expandable == TRUE)
		return (TRUE);
	return (FALSE);
}

t_bool	need_to_be_expand(t_minishell *ms, char **tokens)
{
	int	k;
	int	count;

	if (!tokens || !*tokens)
		return (FALSE);
	k = 0;
	count = count_tokens(tokens);
	while (tokens[k] && k < count)
	{
		if (is_expandable(ms, tokens[k], k) == TRUE && !is_heredoc_delim(ms,
				tokens, k))
			return (TRUE);
		k++;
	}
	return (FALSE);
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
