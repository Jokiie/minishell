/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_only.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:59:12 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/04 23:16:50 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	contains_only_digits(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	contains_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	contains_only_type(char **tokens, int **protected,
		t_bool (*is_type)(char *))
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if ((*protected)[i] == 0 && !is_type(tokens[i]))
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}

t_bool	contains_only_quotes(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_is_squote(token[i]) || ft_is_dquote(token[i]))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}
