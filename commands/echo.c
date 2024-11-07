// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   echo.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
// /*   Updated: 2024/11/05 16:05:19 by matislessar      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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
	int	opt;

	opt = 0;
	if (((k == 0) && ft_strncmp(ms->tokens[k], "echo\0", 5) == 0
			&& ft_strncmp(ms->tokens[k + 1], "-n\0", 3) == 0))
	{
		opt = 1;
	}
	else if ((k == 0) && ft_strncmp(ms->tokens[k], "echo\0", 5) == 0)
	{
		echo(ms->tokens, opt);
		ms->ret = SUCCESS;
	}
	else
	{
		ms->ret = CMD_NOT_FOUND;
	}
	return (ms->ret);
}

/* Prints the tokens after echo */
void	echo(char **tokens, int opt)
{
	int	k;

	k = 1;
	if (!tokens[k])
	{
		write(1, "\n", 1);
		return ;
	}
	while (tokens[k])
	{

		ft_putstr_fd(tokens[k], 1);
		if (tokens[k])
			ft_putstr_fd(" ", 1);
		k++;
	}
	if (!opt)
		ft_putstr_fd("\n", 1);
}
