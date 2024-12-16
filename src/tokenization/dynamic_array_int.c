/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:20:37 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 16:59:15 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    *init_token_state_array(t_minishell *ms, size_t initial_capacity, int k)
{
    ms->token.state_array[k] = ft_calloc(initial_capacity, sizeof(int));
    ms->token.state_array_size = 0;
    ms->token.state_array_capacity = initial_capacity;
    return (ms->token.state_array[k]);    
}

int add_to_state_array(t_minishell *ms, int data, int k)
{
    size_t  new_capacity;
    int   *new_data;
    
    while (ms->token.state_array_size >= ms->token.state_array_capacity - 1)
    {
        new_capacity = ms->token.state_array_capacity * 5;
        new_data = ft_calloc(new_capacity, sizeof(int));
        ft_memcpy(new_data, ms->token.state_array[k], ms->token.state_array_capacity * sizeof(int));
        free_int_array(&ms->token.state_array[k]);
        ms->token.state_array[k] = new_data;
        ms->token.state_array_capacity = new_capacity;
    }
    ms->token.state_array[k][ms->token.state_array_size] = data;
    ms->token.state_array_size++;
    return (0);
}

int    *init_new_state_array(t_minishell *ms, size_t initial_capacity, int k)
{
    ms->token.new_state_array[k] = ft_calloc(initial_capacity, sizeof(int));
    ms->token.new_state_array_size = 0;
    ms->token.new_state_array_capacity = initial_capacity;
    return (ms->token.new_state_array[k]);    
}

int add_to_new_state_array(t_minishell *ms, int data, int k)
{
    size_t  new_capacity;
    int   *new_data;
    
    if (ms->token.new_state_array_size >= ms->token.new_state_array_capacity - 1)
    {
        new_capacity = ms->token.new_state_array_capacity * 5;
        new_data = ft_calloc(new_capacity, sizeof(int));
        ft_memcpy(new_data, ms->token.new_state_array[k], ms->token.new_state_array_capacity * sizeof(int));
        free_int_array(&ms->token.new_state_array[k]);
        ms->token.new_state_array[k] = new_data;
        ms->token.new_state_array_capacity = new_capacity;
    }
    ms->token.new_state_array[k][ms->token.new_state_array_size] = data;
    ms->token.new_state_array_size++;
    return (0);
}

void    fill_new_state_array(t_minishell *ms, int end, int k)
{
    int i;
 
    i = ms->token.expansion_start;
    while (i < end)
    {
        add_to_new_state_array(ms, ms->token.state_array[k][i], k);
        i++;
    }
}

void    fill_3_new_state_array(t_minishell *ms, int start, int len, int k)
{
    int i;
    int state;

    i = start;
    if (ms->token.state_array[k][ms->token.state_index] == 2 || ms->token.state_array[k][ms->token.state_index] == 4)
        state = DQUOTE_EXP;
    else
        state = EXPANSION;
    while (i < start + len)
    {
        add_to_new_state_array(ms, state, k);
        i++;
    }
}

