/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:33:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 04:42:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_bool has_redirect(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (is_redirect(tokens[i]))
           return (TRUE);
        i++;
    }
    return (FALSE);
}

t_bool has_heredoc(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (is_heredoc(tokens[i]))
           return (TRUE);
        i++;
    }
    return (FALSE);
}

t_bool has_pipe(char *input)
{
    int i;

    i = 0;
    if (input)
    {
        while (input[i])
        {
            if (input[i] == '|')
                return (TRUE);
            i++;
        }
    }
    return (FALSE);
}
