/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/17 13:56:01 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Call the pwd command, Return the 0 is successful, 1 if too many arguments,
	and -1 if the command(pwd) is not found.
*/
int	detect_pwd_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(tokens[0], "pwd\0", 4) == 0)
	{
		ms->ret = pwd(ms, tokens);
		return (ms->ret);
	}
	ms->ret = CMD_NOT_FOUND;
	return (ms->ret);
}

/* Display the current working directory */
int	pwd(t_minishell *ms, char **tokens)
{

	if (tokens[1] != NULL)
	{
		ft_fprintf(2, "pwd: too many arguments\n");
		return (ERROR);
	}
	ft_printf("%s\n", ms->cwd);
	return (SUCCESS);
}
