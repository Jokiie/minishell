/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:48:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/23 05:21:25 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **cleaner(char **tokens)
{
    char    **cleaned;
    char    *tmp;
    int     count;
    int     k;
    int     i;
    
    k = 0;
    i = 0;
    if (!tokens)
		return (NULL);
    count = count_valid_tokens(tokens);
    cleaned = ft_calloc(count + 2, sizeof(char *));
    if (!cleaned)
    {
        free(tokens);
        return (NULL);
    }
    while (tokens[k] && k < count)
    {
        if (tokens[k][0])
        {
            tmp = tokens[k];
            cleaned[i] = ft_strdup(tokens[k]);
            if (cleaned)
		    {
			    i++;
		    }
            else
            {
                ft_free(tmp);
            }
        }
        k++;
    }
    if (!cleaned[0])
	{
		free(cleaned);
		return (NULL);
	}
    cleaned[i] = NULL;
    return (cleaned);
}

t_bool    has_empty_token(char **tokens)
{
    int    k;
    int    count;
    
    k = 0;
    count = count_tokens(tokens);
    while (k < count)
    {
        if (k != count && !tokens[k][0])
        {
            ft_fprintf(2, "has empty token\n");
            return (TRUE);
        }
        k++;
    }
    return (FALSE);
}

int count_valid_tokens(char **tokens)
{
    int    k;
    int    count;
    
    k = 0;
    count = count_tokens(tokens);
    while (tokens[k])
    {
        if (tokens[k][0] != '\0')
        {
            count++;
        }
        k++;
    }
    return (count);
}
