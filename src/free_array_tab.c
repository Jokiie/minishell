/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:57:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/27 23:47:18 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens_address(char ***tokens)
{
	int	i;

	if (tokens && *tokens)
	{
		i = 0;
		while ((*tokens)[i])
		{
			free_ptr((*tokens)[i]);
			i++;
		}
		free(*tokens);
		*tokens = NULL;
	}
}

void	free_tokens(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	if (tokens)
	{
		count = count_tokens(tokens);
		while (tokens[i] && i < (count))
		{
			free_ptr(tokens[i]);
			i++;
		}
		free(tokens);
		tokens = NULL;
	}
}
