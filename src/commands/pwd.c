/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/21 16:01:56 by ccodere          ###   ########.fr       */
=======
/*   Updated: 2024/11/21 14:54:27 by matislessar      ###   ########.fr       */
>>>>>>> origin/cmd
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
	Display the current working directory, if the cwd do not exist,
	display the previous cwd. But maybe need to enhance this because
	if we delete a parent directory, it do not display properly. At
	least it do not segfault.
*/
int	pwd(t_minishell *ms)
{
	int	return_value;

	return_value = 0;
	if (!ms->cwd)
	{
		//should print the deleted directory
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
