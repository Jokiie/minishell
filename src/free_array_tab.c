/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:57:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/18 15:38:49 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens_address(char ***tokens)
{
	int	i;

	if (tokens && *tokens)
	{
		i = 0;
		while ((*tokens)[i])
		{
			free_ptr((*tokens)[i]);
			i++;
		}
		free(*tokens);
		*tokens = NULL;
	}
}

void	free_tokens(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	if (tokens)
	{
		count = count_tokens(tokens);
		while (tokens[i] && i < (count))
		{
			free_ptr(tokens[i]);
			i++;
		}
		free(tokens);
		tokens = NULL;
	}
}

void	free_state_array(t_minishell *ms, int count)
{
	int	i;

	if (ms->token.state_array)
	{
		i = 0;
		while (ms->token.state_array[i] && i < count)
		{
			free_int_array(&ms->token.state_array[i]);
			i++;
		}
		free(ms->token.state_array);
		ms->token.state_array = NULL;
	}
}

void	free_dbuffer(t_minishell *ms)
{
	size_t	i;

	i = 0;
	if (!ms->token.db_buffer)
		return ;
	while (i < ms->token.db_size)
	{
		if (ms->token.db_buffer[i])
			free(ms->token.db_buffer[i]);
		i++;
	}
	free(ms->token.db_buffer);
	ms->token.db_buffer = NULL;
	ms->token.db_size = 0;
	ms->token.db_capacity = 0;
}
