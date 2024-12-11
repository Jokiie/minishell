/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 05:43:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/10 02:56:21 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_debug(char **tokens)
{
	int	k;
	int	count;

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

void	print_int_array(char **tokens, int **quoted)
{
	int	i;
	int	count;

	i = 0;
	count = count_tokens(tokens);
	while (i < count)
	{
		if (tokens[i])
			ft_fprintf(2, YELLOW "quoted[%d] = %d\n" RESET, i, (*quoted)[i]);
		else
			ft_fprintf(2, YELLOW "quoted[%d] = (null)\n" RESET, i);
		i++;
	}
}

void	print_expanded_array(char **tokens, int **expanded)
{
	int	i;
	int	count;

	i = 0;
	count = count_tokens(tokens);
	while (i < count)
	{
		if (tokens[i])
			ft_fprintf(2, YELLOW "expanded[%d] = %d\n" RESET, i,
				(*expanded)[i]);
		else
			ft_fprintf(2, YELLOW "expanded[%d] = (null)\n" RESET, i);
		i++;
	}
}

void	print_cexpanded_array(char **tokens, int **cexpanded)
{
	int	i;
	int	j;
	int	count;
	int size;

	count = count_tokens(tokens);
	i = 0;
	while (i < count)
	{
		j = 0;
		size = ft_strlen(tokens[i]);
		while (j < size)
		{
			ft_fprintf(2, "[%d]", cexpanded[i][j]);
			j++;
		}
		ft_fprintf(2, "\n");
		i++;
	}
}
