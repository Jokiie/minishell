/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_one_meta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:08:21 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/05 15:18:10 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_bool	has_redirect_in(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect_in(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_redirect_out(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect_out(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_append(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_append(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_heredoc(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_heredoc(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_pipe(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
