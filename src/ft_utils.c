/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:33:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/16 14:17:23 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens || !*tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

void	ft_print_tokens(char **tokens)
{
	int	k;

	k = 0;
	if (!tokens || !*tokens)
		return ;
	while (tokens[k])
	{
		ft_printf(":%s:\n", tokens[k]);
		k++;
	}
}
