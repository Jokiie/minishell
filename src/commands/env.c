/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:40:51 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 06:41:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Call the env command, return 0 is successfull, 1 for errors and
	CMD_NOT_FOUND(127) if the command(pwd) is not found.
*/
int	detect_env_call(t_minishell *ms, char **tokens)
{
	int	return_value;

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
		ft_printf("ms: env: %s\n", strerror(errno));
		return_value = ERROR;
	}
	return (return_value);
}
