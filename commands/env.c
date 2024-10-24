/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:04:19 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/24 13:40:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Call the env command, return 0 is successfull, 1 for errors and
	CMD_NOT_FOUND(127) if the command(pwd) is not found.
*/
int	detect_env_call(t_minishell *ms, int k)
{
	if ((k == 0) && strncmp(ms->tokens[k], "env\0", 4) == 0)
	{
		ms->ret = env(ms, k);
	}
	else
	{
		ms->ret = CMD_NOT_FOUND;
	}
	return (ms->ret);
}

/* Display the ms->env */
int	env(t_minishell *ms, int k)
{
	if (ms->tokens[k + 1])
	{
		ft_fprintf(2, "ms: env: too many arguments\n");
		ms->ret = ERROR;
	}
	else if (!ms->tokens[k + 1] && (ms->env))
	{
		ft_print_tokens(ms->env);
		ms->ret = SUCCESS;
	}
	else
	{
		ft_printf("ms: env: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
}
