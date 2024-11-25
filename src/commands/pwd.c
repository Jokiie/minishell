/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:49:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 06:49:19 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Call the pwd command, Return the 0 is successful, 1 if too many arguments,
	and CMD_NOT_FOUND(127) if the command(pwd) is not found.
*/
int	detect_pwd_call(t_minishell *ms, char **tokens)
{
	int	return_value;

	return_value = 0;
	if (ft_strncmp(tokens[0], "pwd\0", 4) == 0)
		return_value = pwd(ms);
	else
		return_value = CMD_NOT_FOUND;
	return (return_value);
}

/*
	Display the current working directory
*/
int	pwd(t_minishell *ms)
{
	int	return_value;

	return_value = 0;
	if (!ms->cwd)
	{
		ft_putstr_fd("You are in a deleted directory, ", 2);
		ft_putstr_fd("please 'cd ..' until you are in a valid directory\n", 2);
		return_value = SUCCESS;
	}
	else
	{
		ft_printf("%s\n", ms->cwd);
		return_value = SUCCESS;
	}
	return (return_value);
}
