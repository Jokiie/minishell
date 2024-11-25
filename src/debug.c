/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 05:43:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 04:18:54 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_debug(char **tokens)
{
	int	k;

	k = 0;
	if (!tokens || !*tokens)
	{
		ft_fprintf(2, GREEN "[0] = (null)\n" RESET);
		return ;
	}
	while (tokens[k])
	{
		ft_fprintf(2, GREEN "[%d] = :%s:\n" RESET, k, tokens[k]);
		k++;
	}
}

void	print_protected_array(char **tokens, int **protected)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		ft_fprintf(2, YELLOW "protected[%d] = %d\n" RESET, i, (*protected)[i]);
		i++;
	}
}
