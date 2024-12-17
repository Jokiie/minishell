/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_array_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:30:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/17 03:37:20 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_expanded_state(t_minishell *ms, char **tokens, int k)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(tokens[k]);
	while (tokens[k][i] && i < len)
	{
		if (ms->token.state_array[k][i] >= 3)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_quoted_state(t_minishell *ms, int start, int len, int k)
{
	int	i;

	i = start;
	while (i < len)
	{
		if (ms->token.state_array[k][i] == 1 || ms->token.state_array[k][i] == 2
			|| ms->token.state_array[k][i] == 4)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	fill_new_state_array(t_minishell *ms, int end, int k)
{
	int	i;

	i = ms->token.expansion_start;
	while (i < end)
	{
		add_to_new_state_array(ms, ms->token.state_array[k][i], k);
		i++;
	}
}

void	fill_3_new_state_array(t_minishell *ms, int start, int len, int k)
{
	int	i;
	int	state;

	i = start;
	if (ms->token.state_array[k][ms->token.state_index] == 2
		|| ms->token.state_array[k][ms->token.state_index] == 4)
		state = DQUOTE_EXP;
	else
		state = EXPANSION;
	while (i < start + len)
	{
		add_to_new_state_array(ms, state, k);
		i++;
	}
}
