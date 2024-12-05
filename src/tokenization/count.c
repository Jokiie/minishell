/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 05:27:46 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 01:13:26 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_type(char **tokens, int **quoted, int **expanded, t_bool (*is_type)(char *))
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (is_type(tokens[i]) && (*quoted)[i] == 0 && (*expanded)[i] == 0)
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

int	count_size(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		count += ft_strlen(tokens[i]);
		i++;
	}
	return (count);
}
