/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/07 03:22:17 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
