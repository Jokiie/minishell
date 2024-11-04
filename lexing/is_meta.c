/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_meta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 04:42:17 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 04:42:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_bool is_redirect(char *token)
{
    if (ft_strncmp(token, ">", 2) == 0
        || ft_strncmp(token, "<", 2) == 0
        || ft_strncmp(token, ">>", 3) == 0)
        return (TRUE);
    return (FALSE);
}

t_bool is_heredoc(char *token)
{
    if (ft_strncmp(token, "<<", 3) == 0)
        return (TRUE);
    return (FALSE);
}

t_bool is_pipe(char *token)
{
    if (ft_strncmp(token, "|", 2) == 0)
        return (TRUE);
    return (FALSE);
}
