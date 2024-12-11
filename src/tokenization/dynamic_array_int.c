/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:20:37 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/11 03:09:09 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    *init_cexpanded_int(t_minishell *ms, size_t initial_capacity, int cexpindex)
{
    ms->token.cexpanded[cexpindex] = ft_calloc(initial_capacity + 1, sizeof(int));
    if (!ms->token.cexpanded[cexpindex])
        return (NULL);
    ms->token.cexp_size = 0;
    ms->token.cexp_capacity = initial_capacity + 1;
    return (ms->token.cexpanded[cexpindex]);    
}

int append_to_cexpanded(t_minishell *ms, int data, int cexpindex)
{
    size_t  new_capacity;
    int   *new_data;
    
    while (ms->token.cexp_size >= ms->token.cexp_capacity)
    {
        new_capacity = ms->token.cexp_capacity * 3;
        new_data = ft_calloc(new_capacity, sizeof(int));
        ft_memcpy(new_data, ms->token.cexpanded[cexpindex], ms->token.cexp_capacity * sizeof(int));
        free_int_array(&ms->token.cexpanded[cexpindex]);
        ms->token.cexpanded[cexpindex] = new_data;
        ms->token.cexp_capacity = new_capacity;
    }
    ms->token.cexpanded[cexpindex][ms->token.cexp_size] = data;
    ms->token.cexp_size++;
    return (0);
}

void    fill_0_cexpanded(t_minishell *ms, int start, int len, int cexpindex)
{
    int i;

    i = start;
    while (i < start + len)
    {
        append_to_cexpanded(ms, 0, cexpindex);
        i++;
    }  
}

void    fill_1_cexpanded(t_minishell *ms, int start, int len, int cexpindex)
{
    int i;

    i = start;
    while (i < start + len)
    {
        append_to_cexpanded(ms, 1, cexpindex);
        i++;
    }  
}

int    **init_dbuffer_intp(t_minishell *ms, size_t initial_capacity)
{
    ms->token.db_buffer_intp = ft_calloc(initial_capacity + 1, sizeof(int *));
    if (!ms->token.db_buffer_intp)
        return (NULL);
    ms->token.db_size = 0;
    ms->token.db_capacity = initial_capacity + 1;
    return (ms->token.db_buffer_intp);    
}

int append_to_dbuffer_intp(t_minishell *ms, int *data)
{
    size_t  new_capacity;
    int   **new_data;

    if (!ms->token.db_buffer_intp)
    {
        ms->token.db_buffer_intp = NULL;
        return (-1);
    }
    while (ms->token.db_size >= ms->token.db_capacity)
    {
        new_capacity = ms->token.db_capacity * 3;
        new_data = ft_realloc(ms->token.db_buffer_intp, ms->token.db_capacity * sizeof(int *), new_capacity * sizeof(int *));
        if (!new_data)
            return (-1);
        ms->token.db_buffer_intp = new_data;
        ms->token.db_capacity = new_capacity;
    }
    ms->token.db_buffer_intp[ms->token.db_size] = data;
    return (0);
}