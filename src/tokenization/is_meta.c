/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_meta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:13:36 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/19 03:43:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool  is_redirect(char *token)
{
    if (is_redirect_in(token) || is_redirect_out(token) || is_append(token))
        return (TRUE);
    return (FALSE);
}

t_bool is_meta(char *token)
{
    if (is_heredoc(token) || is_redirect(token) || is_pipe(token))
        return (TRUE);
    return (FALSE);
}