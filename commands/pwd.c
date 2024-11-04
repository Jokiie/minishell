/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 05:18:22 by ccodere          ###   ########.fr       */
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
		ms->ret = pwd(ms);
	}
	else
	{
		ms->ret = CMD_NOT_FOUND;
	}
	return (ms->ret);
}

/*
	Display the current working directory, if the cwd do not exist,
	display the previous cwd. But maybe need to enhance this because
	if we delete a parent directory, it do not display properly. At
	least it do not segfault.
*/
int	pwd(t_minishell *ms)
{
	if (!ms->cwd)
	{
		ft_printf("%s\n", ms->prev_cwd);
		ms->ret = SUCCESS;
	}
	else 
	{
		ft_printf("%s\n", ms->cwd);
		ms->ret = SUCCESS;
	}
	return (ms->ret);
}
