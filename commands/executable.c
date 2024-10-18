/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:14:31 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/17 22:28:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Detect if the command is an executable. If the command couldn't be executed, 
	return CMD_NOT_FOUND(127) , else return 0. If the the token to not begin
	with "./", return -1 , so we can check the other built-in commands.	
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
