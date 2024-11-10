/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_one_meta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:13:47 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/09 22:30:54 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_bool  is_redirect_in(char *token)
{
    if (ft_strncmp(token, "<", 2) == 0)
        return (TRUE);
    return (FALSE);
}

t_bool is_redirect_out(char *token)
{
    if (ft_strncmp(token, ">", 2) == 0)
        return (TRUE);
    return (FALSE);
}

t_bool  is_append(char *token)
{
    if (ft_strncmp(token, ">>", 3) == 0)
        return (TRUE);
    return (FALSE);
}

t_bool  is_heredoc(char *token)
{
    if (ft_strncmp(token, "<<", 3) == 0)
        return (TRUE);
    return (FALSE);
}

t_bool  is_pipe(char *token)
{
    if (ft_strncmp(token, "|", 2) == 0)
        return (TRUE);
    return (FALSE);
}
