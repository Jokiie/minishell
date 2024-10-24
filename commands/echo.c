/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/24 15:13:59 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Detect if the command is echo, currently work if only the first token
	is echo. If the echo call is detected, call echo. Return 0 is successful,
	and CMD_NOT_FOUND(127) is the call is not detected.
	to do :
	- should work later if a pipe preceed it.
		as for the example : ls | echo done
		which should print 'done' and not the result of ls.
*/
int	detect_echo_call(t_minishell *ms, int k)
{
	if (((k == 0) && ft_strncmp(ms->tokens[k], "echo\0", 5) == 0
			&& ft_strncmp(ms->tokens[k + 1], "-n\0", 3) == 0))
	{
		echo_n(ms->tokens);
		ms->ret = SUCCESS;
	}
	else if ((k == 0) && ft_strncmp(ms->tokens[k], "echo\0", 5) == 0)
	{
		echo(ms->tokens);
		ms->ret = SUCCESS;
	}
	else
	{
		ms->ret = CMD_NOT_FOUND;
	}
	return (ms->ret);
}

/* Prints the tokens after echo */
void	echo(char **tokens)
{
	int	k;

	k = 1;
	if (!tokens[k])
	{
		write(1, "\n", 1);
		return ;
	}
	while (tokens[k + 1])
	{
		ft_printf("%s ", tokens[k]);
		k++;
	}
	ft_printf("%s\n", tokens[k]);
}

/* Prints the tokens after echo -n and print a surligned '%' at the end.*/
void	echo_n(char **tokens)
{
	int	k;

	k = 2;
	if (!tokens[k])
		return ;
	while (tokens[k + 1])
	{
		ft_printf("%s ", tokens[k]);
		k++;
	}
	ft_printf("%s", tokens[k]);
	ft_printf(SURL "%%\n" SURLRESET);
}
