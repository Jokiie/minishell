/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 03:59:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/10 19:15:50 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    Init a dynamic char **buffer with a capacity of initial_capacity + 1.
*/
char    **init_dbuffer(t_minishell *ms, size_t initial_capacity)
{
    ms->token.db_buffer = ft_calloc(initial_capacity + 1, sizeof(char *));
    if (!ms->token.db_buffer)
        return (NULL);
    ms->token.db_size = 0;
    ms->token.db_capacity = initial_capacity + 1;
    return (ms->token.db_buffer);
}

/*
    Append a char * to the ms->token.db_buffer.
*/
int append_to_dbuffer_char(t_minishell *ms, char *data, int expanded_state)
{
    size_t  new_capacity;
    char   **new_data;
    int     *new_expanded;
    
    if (!ms->token.db_buffer)
    {
        ms->token.db_buffer = NULL;
        return -1;
    }
    while (data && ms->token.db_size >= ms->token.db_capacity)
    {
        new_capacity = ms->token.db_capacity * 3;
        new_data = ft_realloc(ms->token.db_buffer, ms->token.db_capacity * sizeof(char *), new_capacity * sizeof(char *));
        if (!new_data)
            return (-1);
        ms->token.db_buffer = new_data;
        new_expanded = ft_calloc(new_capacity, sizeof(int));
        if (!new_expanded)
            return (-1);
        ft_memcpy(new_expanded, ms->token.expanded, ms->token.db_capacity * sizeof(int));
        free_int_array(&ms->token.expanded);
        free(ms->token.expanded);
        ms->token.expanded = new_expanded;
        ms->token.db_capacity = new_capacity;
    }
    ms->token.db_buffer[ms->token.db_size] = data;
    if (data)
        ms->token.expanded[ms->token.db_size] = expanded_state;
    ms->token.db_size++;
    return (0);
}

void free_dbuffer(t_minishell *ms)
{
    size_t i;

    if (!ms->token.db_buffer)
        return;
    for (i = 0; i < ms->token.db_size; i++)
    {
        if (ms->token.db_buffer[i])
            free(ms->token.db_buffer[i]);
    }
    free(ms->token.db_buffer);
    ms->token.db_buffer = NULL;
    ms->token.db_size = 0;
    ms->token.db_capacity = 0;
}
