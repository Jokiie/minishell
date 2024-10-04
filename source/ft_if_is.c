/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:18:41 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 00:24:34 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_dquote(int c)
{
    return (c == '\"');
}

int ft_is_squote(int c)
{
    return (c == '\'');
}

int ft_isquotes(int c)
{
    return (ft_is_dquote(c) || ft_is_squote(c));
}

int ft_isredirect(int c)
{
    return (c == '<' || c == '>');
}

int ft_isnull(int c)
{
    return (c == '\0');
}