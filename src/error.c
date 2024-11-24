/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/24 09:46:05 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *cmd)
{
	int return_value;
	
	return_value = 0;
	if (errno == EISDIR)
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		return_value = CPERM_DENIED;
	}
	else if (errno == ENOENT)
	{
		if (cmd[0] == '/')
			ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		else
			ft_fprintf(2, "ms: %s: command not found\n", cmd);
		return_value = CMD_NOT_FOUND;
	}
	else if (errno == EACCES)
	{
		if (cmd[0] == '/')
		{
			errno = EISDIR;
			ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		}
		else
			ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		return_value = CPERM_DENIED;
	}
	else if (errno == ENAMETOOLONG)
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		return_value = CMD_NOT_FOUND;
	}
	else
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		return_value = ERROR;
	}
	return (return_value);
}
