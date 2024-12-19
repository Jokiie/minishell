/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_state_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:36:34 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 11:36:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Init the state_array which is a dynamic buffer that store the state of
    each characters:
	0 - normal
	1 - single quoted - SQUOTE
	2 - double quoted - DQUOTE
	3 - expanded - EXPANSION
	4 - expanded and double quoted DQUOTE_EXP
*/
int	*init_token_state_array(t_minishell *ms, size_t initial_capacity, int k)
{
	ms->token.state_array[k] = ft_calloc(initial_capacity, sizeof(int));
	ms->token.state_array_size = 0;
	ms->token.state_array_capacity = initial_capacity;
	return (ms->token.state_array[k]);
}

int	add_to_state_array(t_minishell *ms, int data, int k)
{
	size_t	new_capacity;
	int		*new_data;

	while (ms->token.state_array_size >= ms->token.state_array_capacity - 1)
	{
		new_capacity = ms->token.state_array_capacity * 5;
		new_data = ft_calloc(new_capacity, sizeof(int));
		ft_memcpy(new_data, ms->token.state_array[k],
			ms->token.state_array_capacity * sizeof(int));
		free_int_array(&ms->token.state_array[k]);
		ms->token.state_array[k] = new_data;
		ms->token.state_array_capacity = new_capacity;
	}
	ms->token.state_array[k][ms->token.state_array_size] = data;
	ms->token.state_array_size++;
	return (0);
}

int	*init_new_state_array(t_minishell *ms, size_t initial_capacity, int k)
{
	ms->token.new_state_array[k] = ft_calloc(initial_capacity, sizeof(int));
	ms->token.new_state_array_size = 0;
	ms->token.new_state_array_capacity = initial_capacity;
	return (ms->token.new_state_array[k]);
}

int	add_to_new_state_array(t_minishell *ms, int data, int k)
{
	size_t	new_capacity;
	int		*new_data;

	if (ms->token.new_state_array_size >= ms->token.new_state_array_capacity
		- 1)
	{
		new_capacity = ms->token.new_state_array_capacity * 5;
		new_data = ft_calloc(new_capacity, sizeof(int));
		ft_memcpy(new_data, ms->token.new_state_array[k],
			ms->token.new_state_array_capacity * sizeof(int));
		free_int_array(&ms->token.new_state_array[k]);
		ms->token.new_state_array[k] = new_data;
		ms->token.new_state_array_capacity = new_capacity;
	}
	ms->token.new_state_array[k][ms->token.new_state_array_size] = data;
	ms->token.new_state_array_size++;
	return (0);
}
