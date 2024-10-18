/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:14:31 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 13:41:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Detect if the command is an executable. If exerve fail, we check if the
	error is because we don't have permissions or if the file do not exist.
	Else if exerve success, we return SUCCESS(0).
	Else if the the token do not begin with "./", return CMD_NOT_FOUND(127),
	so we can check the other built-in commands.
*/
int	detect_executable(t_minishell *ms, char **tokens, int k)
{
	if (tokens[k][0] == '.' && tokens[k][1] == '/')
	{
		if (execve(tokens[k], tokens, ms->env) == FAIL)
		{
			if (errno == EACCES)
			{
				ft_fprintf(2, "ms: permission denied: %s\n", tokens[k]);
				ms->ret = CPERM_DENIED;
				return (ms->ret);
			}
			else if (errno == ENOENT)
			{
				ft_fprintf(2, "ms: no such file or directory: %s\n", tokens[k]);
				ms->ret = CMD_NOT_FOUND;
				return (ms->ret);
			}
		}
		ms->ret = SUCCESS;
		return (ms->ret);
	}
	ms->ret = CMD_NOT_FOUND;
	return (ms->ret);
}
