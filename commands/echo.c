/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/14 12:23:43 by ccodere          ###   ########.fr       */
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
int	detect_echo_call(t_minishell *ms)
{
	int	opt;

	opt = 0;
	if (ft_strncmp(ms->tokens[0], "echo\0", 5) == 0)
	{
		if (ft_strncmp(ms->tokens[1], "-n\0", 3) == 0)
			opt = 1;
		echo(ms, ms->tokens, opt);
		return (SUCCESS);
	}
	return (CMD_NOT_FOUND);
}

/* Prints the tokens after echo */
void	echo(t_minishell *ms, char **tokens, int opt)
{
	int	k;

	if (opt == 0)
		k = 1;
	else
		k = 2;
	if (!tokens[k])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	while (tokens[k])
	{
		if (ms->token.protected[k] && ft_strcmp(tokens[k], "|") == 0)
		{
			break ;
		}
		ft_putstr_fd(tokens[k], STDOUT_FILENO);
		if (tokens[k])
			ft_putstr_fd(" ", STDOUT_FILENO);
		k++;
	}
	if (!opt)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
