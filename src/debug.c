/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 05:43:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/30 00:22:38 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_debug(char **tokens)
{
	int	k;
	int count;
	
	k = 0;
	if (!tokens || !*tokens)
	{
		ft_fprintf(2, GREEN "[0] = (null)\n" RESET);
		return ;
	}
	count = count_tokens(tokens);
	while (k < count)
	{
		if (tokens[k])
			ft_fprintf(2, GREEN "[%d] = :%s:\n" RESET, k, tokens[k]);
		else
			ft_fprintf(2, GREEN "[%d] = (null)\n" RESET, k);	
		k++;
	}
}

void	print_protected_array(char **tokens, int **protected)
{
	int	i;
	int	count;

	i = 0;
	count = count_tokens(tokens);
	while (i < count)
	{
		if (tokens[i])
			ft_fprintf(2, YELLOW "protected[%d] = %d\n" RESET, i, (*protected)[i]);
		else
			ft_fprintf(2, YELLOW "protected[%d] = (null)\n" RESET, i);
		i++;
	}
}
