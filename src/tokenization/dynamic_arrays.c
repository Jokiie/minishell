/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 03:59:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/09 01:31:28 by ccodere          ###   ########.fr       */
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
int append_to_dbuffer_char(t_minishell *ms, char *data)
{
    size_t  new_capacity;
    char   **new_data;

    if (!data)
        return (-1); 
    while ((ms->token.db_size + 1) > ms->token.db_capacity)
    {
        new_capacity = ms->token.db_capacity * 2;
        new_data = ft_realloc(ms->token.db_buffer, ms->token.db_capacity * sizeof(char *), new_capacity * sizeof(char *));
        if (!new_data)
            return (-1);
        ms->token.db_buffer = new_data;
        ms->token.db_capacity = new_capacity;
    }
    ms->token.db_buffer[ms->token.db_size] = data;
    ms->token.db_size++;
    return (0);
}

// int append_to_dbuffer_int(t_minishell *ms, int *data, size_t data_count)
// {
//     size_t  new_capacity;
//     int     **new_data;
//     size_t  i;

//     if (!data)
//         return (-1);
    
//     while ((ms->token.db_size + data_count) >= ms->token.db_capacity)
//     {
//         new_capacity = ms->token.db_capacity * 2;
//         new_data = ft_realloc(ms->token.db_idata, ms->token.db_capacity * sizeof(int *), new_capacity * sizeof(int *));
//         if (!new_data)
//             return (-1);
//         ms->token.db_idata = new_data;
//         ms->token.db_capacity = new_capacity;
//     }
//     i = 0;
//     while (i < data_count)
//     {
//         ms->token.db_idata[ms->token.db_size] = data[i];
//         ms->token.db_size++;
//         i++;
//     }
//     return (0);
// }
