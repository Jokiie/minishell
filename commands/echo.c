/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 00:56:05 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*	
	Detect if the command is echo, currently work if only the first token
	is echo. But this should work later if a pipe preceed it.
	as for the example : ls | echo done
	which should print 'done' and not the result of ls.
	if the echo call is detected, print the tokens. return 0 is successful,
	and -1 if the call is not found.
*/
int	detect_echo_call(t_minishell *ms, char **tokens, int k)
{
	if ((ft_strncmp(tokens[0], "echo\0", 5) == 0
		&& ft_strncmp(tokens[k + 1], "-n\0", 3) == 0))
	{
		echo_n(tokens);
		ms->ret = SUCCESS;
		return (SUCCESS);
	}
	else if (ft_strncmp(tokens[0], "echo\0", 5) == 0)
	{
		echo(tokens);
		ms->ret = SUCCESS;
		return (SUCCESS);
	}
	return (CMD_NOT_FOUND);
}

/* Print the tokens after echo */
void	echo(char **tokens)
{
	int	k;

	k = 1;
	if (!tokens[k])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
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
