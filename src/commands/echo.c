/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:41:24 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/02 05:08:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Detect if the command is echo, If the echo call is detected, call echo.
	Return 0 is successful, and CMD_NOT_FOUND(127) is the call is not detected.
*/
int	detect_echo_call(t_minishell *ms, char **tokens)
{
	int	opt;

	opt = 0;
	if (ft_strncmp(tokens[0], "echo\0", 5) == 0)
	{
		if (tokens[1] && valid_echo_arg(tokens[1]) == TRUE)
			opt = 1;
		echo(ms, tokens, opt);
		return (SUCCESS);
	}
	return (CMD_NOT_FOUND);
}

/* Prints the tokens after echo */
void	echo(t_minishell *ms, char **tokens, int opt)
{
	int	k;
	int	first_word;

	(void)ms;
	first_word = 1;
	if (opt == 1)
		k = update_echo_index(tokens, &k);
	else
		k = 1;
	while (tokens[k])
	{
		if (!first_word)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(tokens[k], STDOUT_FILENO);
		first_word = 0;
		k++;
	}
	if (!opt)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	update_echo_index(char **tokens, int *k)
{
	*k = 2;
	while (tokens[*k])
	{
		if (valid_echo_arg(tokens[*k]) == TRUE)
			(*k)++;
		else
			break ;
	}
	return (*k);
}

t_bool	valid_echo_arg(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[0] == '-')
			i++;
		if (token[1] != 'n')
			return (FALSE);
		while (token[i] == 'n')
			i++;
		if (token[i] != '\0')
			return (FALSE);
	}
	return (TRUE);
}
