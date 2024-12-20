/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:01:41 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 23:05:58 by ccodere          ###   ########.fr       */
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

int	init_retokenizer(t_minishell *ms, int **ex, int **qt, size_t size)
{
	ms->token.state_index = 0;
	*ex = ft_calloc(size, sizeof(int));
	if (!*ex)
		return (-1);
	ft_memcpy(*ex, ms->token.expanded, sizeof(int) * size);
	*qt = ft_calloc(size, sizeof(int));
	if (!*qt)
	{
		free_int_array(ex);
		return (-1);
	}
	ft_memcpy(*qt, ms->token.quoted, sizeof(int) * size);
	return (0);
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
			if (token[i] == '$' && (ft_isalnum(token[i + 1])
					|| token[i + 1] == '_' || token[i + 1] == '?'))
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

t_bool	is_space_state(t_minishell *ms, char *token, int *i, int k)
{
	if (ft_isspace(token[*i]) && !is_quoted_state(ms, i, k))
	{
		return (TRUE);
	}
	return (FALSE);
}
