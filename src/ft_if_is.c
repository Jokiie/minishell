/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:18:41 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/10 16:48:31 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_dquote(int c)
{
	return (c == '\"');
}

int	ft_is_squote(int c)
{
	return (c == '\'');
}

int	ft_isquotes(int c)
{
	return (ft_is_dquote(c) || ft_is_squote(c));
}

int	ft_isredirect(int c)
{
	return (c == '<' || c == '>');
}

