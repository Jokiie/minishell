/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:04:19 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 15:59:23 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Call the env command, return 0 is successfull, 1 for errors and
	CMD_NOT_FOUND(127) if the command(pwd) is not found.
*/
int	detect_env_call(t_minishell *ms, char **tokens)
{
	int return_value;

	return_value = 0;
	if (ft_strncmp(tokens[0], "env\0", 4) == 0)
		return_value = env(ms, tokens);
	else
		return_value = CMD_NOT_FOUND;
	return (return_value);
}

/* Display the ms->env */
int	env(t_minishell *ms, char **tokens)
{
	int	return_value;

	(void)tokens;
	return_value = 0;
	if (tokens[1])
	{
		// if it a valid argument, execute it
		// examples:
		//
		// env VAR1=value1 VAR2=value2 command
		//
		// env PATH=/custom/path ls - > execute ls in a custom path without modify
		// permanently the path in the env variables.
		//
		// env LANG=fr_FR.UTF-8 date -> date is executed in free but this do not affect
		// the global environment.
		ft_fprintf(2, "ms: env: too many arguments\n");
		return_value = ERROR;
	}
	if (ms->env)
	{
		print_tokens(ms->env);
		return_value = SUCCESS;
	}
	else if (return_value != SUCCESS)
	{
		// should print access denied if the argument is not valid(bash do that)
		ft_printf("ms: env: %s\n", strerror(errno));
		return_value = ERROR;
	}
	return (return_value);
}
