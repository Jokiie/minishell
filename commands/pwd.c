/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/31 12:42:42 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Call the pwd command, Return the 0 is successful, 1 if too many arguments,
	and CMD_NOT_FOUND(127) if the command(pwd) is not found.
*/
int	detect_pwd_call(t_minishell *ms, int k)
{
	if ((k == 0) && ft_strncmp(ms->tokens[k], "pwd\0", 4) == 0)
	{
		ms->ret = pwd(ms, k);
	}
	else
	{
		ms->ret = CMD_NOT_FOUND;
	}
	return (ms->ret);
}

/* Display the current working directory */
int	pwd(t_minishell *ms, int k)
{
	if (ms->tokens[k + 1])
	{
		ft_fprintf(2, "ms: pwd: too many arguments\n");
		ms->ret = ERROR;
	}
	else if (!ms->tokens[k + 1] && ms->cwd)
	{
		ft_printf("%s\n", ms->cwd);
		ms->ret = SUCCESS;
	}
	else if (!ms->cwd)
	{
		chdir(ms->prev_cwd);
		ft_printf("%s\n", ms->prev_cwd);
		ms->ret = SUCCESS;
	}
	else
	{
		ft_printf("ms: pwd: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
}
