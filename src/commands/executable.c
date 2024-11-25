/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:40:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 15:41:26 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Detect if the command is an executable. If execve is successful, we return
	success, else we return the corresponding error code from check_error_exec.
	If the command do not begin with "./" we return EXE_NOT_FOUND.
*/
int	detect_executable(t_minishell *ms, char **tokens)
{
	struct stat	s;

	if (tokens[0][0] == '.' && tokens[0][1] == '/')
	{
		if (stat(tokens[0], &s) == 0)
		{
			if (S_ISDIR(s.st_mode))
			{
				error_msg(tokens[0], "Is a directory");
				return (CPERM_DENIED);
			}
		}
		if (execve(tokens[0], tokens, ms->env) != FAIL)
			return (SUCCESS);
		return (check_error_executable(tokens[0]));
	}
	return (EXE_NOT_FOUND);
}

int	check_error_executable(char *cmd)
{
	int	return_value;

	return_value = 0;
	if (errno == EACCES)
	{
		error_msg(cmd, strerror(errno));
		return_value = CPERM_DENIED;
	}
	else if (errno == ENOENT)
	{
		error_msg(cmd, strerror(errno));
		return_value = CMD_NOT_FOUND;
	}
	else
	{
		error_msg(cmd, strerror(errno));
		return_value = ERROR;
	}
	return (return_value);
}
