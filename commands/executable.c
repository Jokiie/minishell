/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:14:31 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/09 12:51:57 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Detect if the command is an executable. If exerve fail, we check if the
	error is because we don't have permissions , Else if exerve success, we
	return SUCCESS(0). Else if the the token do not begin with "./", return
	CMD_NOT_FOUND(127), so we can check the other built-in commands.
*/
int	detect_executable(t_minishell *ms, int k)
{
	if (ms->tokens[k][0] == '.' && ms->tokens[k][1] == '/')
	{
		if (execve(ms->tokens[k], ms->tokens, ms->env) == FAIL)
		{
			if (errno == EACCES)
			{
				ft_fprintf(2, "ms: %s: %s\n", ms->tokens[k], strerror(errno));
				ms->ret = CPERM_DENIED;
			}
			else if (errno == ENOENT)
			{
				ft_fprintf(2, "ms: %s: %s\n", ms->tokens[k], strerror(errno));
				ms->ret = CMD_NOT_FOUND;
			}
			return (ms->ret);
		}
		return (SUCCESS);
	}
	return (EXE_NOT_FOUND);
}
