/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 05:27:46 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 03:11:33 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_type(char **tokens, int **protected, t_bool (*is_type)(char *))
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (is_type(tokens[i]) && (*protected)[i] == 0)
			count++;
		i++;
	}
	return (count);
}

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens || !*tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}
