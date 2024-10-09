/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/08 21:31:57 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **tokens)
{
	int	k;

	k = 1;
	while (tokens[k + 1])
	{
		ft_printf("%s ", tokens[k]);
		k++;
	}
	ft_printf("%s\n", tokens[k]);
}

void	echo_n(char **tokens)
{
	int	k;

	k = 2;
	while (tokens[k + 1])
	{
		ft_printf("%s ", tokens[k]);
		k++;
	}
	ft_printf("%s", tokens[k]);
	ft_printf(SURL "%%\n" SURLRESET);
}
