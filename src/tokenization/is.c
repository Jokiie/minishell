/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:47:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 06:47:12 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_ismeta_chars(int c)
{
	return (c == '<' || c == '>' || c == '|');
}
