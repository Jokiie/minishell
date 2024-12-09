/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 03:59:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/08 04:20:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dynamic_buffer *init_dbuffer(size_t initial_capacity)
{
    t_dynamic_buffer *buffer;
    
    buffer = malloc(sizeof(t_dynamic_buffer));
    if (!buffer)
        return (NULL);
    buffer->data = malloc(initial_capacity);
    if (!buffer->data)
    {
        free(buffer);
        return (NULL);
    }
    buffer->size = 0;
    buffer->capacity = initial_capacity;
    return (buffer);    
} 

int add_charp_dbuffer(t_dynamic_buffer *buffer, const char *data, size_t data_len)
{
    if (!buffer || !data)
        return (-1);
    size_t  new_capacity;
    char    *new_data;
    
    while (buffer->size + data_len >= buffer->capacity)
    {
        new_capacity = buffer->capacity * 2;
        new_data = ft_realloc(buffer->data, buffer->capacity, new_capacity);
        if (!new_data)
            return (-1);
        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }
    ft_memcpy(buffer->data + buffer->size, data, data_len);
    buffer->size += data_len;
    return (0);
}

int add_intp_dbuffer(t_dynamic_buffer *buffer, const int *data, size_t data_len)
{
    if (!buffer || !data)
        return (-1);
    size_t  new_capacity;
    int    *new_data;
    
    while (buffer->size + data_len >= buffer->capacity)
    {
        new_capacity = buffer->capacity * 2;
        new_data = ft_realloc(buffer->data, buffer->capacity, new_capacity);
        if (!new_data)
            return (-1);
        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }
    ft_memcpy(buffer->data + buffer->size, data, data_len * sizeof(int));
    buffer->size += data_len;
    return (0);
}

void    free_dynamic_buffer(t_dynamic_buffer *buffer)
{
    if (buffer)
    {
        free(buffer->data);
        free(buffer);
    }
}