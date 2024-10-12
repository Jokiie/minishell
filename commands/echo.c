/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 03:40:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*	
	call echo but this currently while it should not : hello echo hello 
	Do not work with redirection either, because redirection is currently
   	called in the fork, in commands.c, which is executed if the custom
	commands failed...
*/
int	detect_echo_call(char **tokens, int i)
{
	if (ft_strnstr(tokens[0], "echo", 4)
		&& ft_strnstr(tokens[i + 1], "-n", 2))
	{
		echo_n(tokens);
		return (SUCCESS);
	}
	if (ft_strnstr(tokens[0], "echo", 4))
	{
		echo(tokens);
		return (SUCCESS);
	}
	return (FAIL);
}

/* Print the tokens after echo */
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

/* Print the tokens after echo -n */
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
