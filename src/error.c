/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 05:34:25 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *cmd)
{
	int	ret;

	ret = 0;
	if (errno == EISDIR)
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		ret = CPERM_DENIED;
	}
	else if (check_enoent(cmd) == CMD_NOT_FOUND)
		ret = CMD_NOT_FOUND;
	else if (check_eacces(cmd) == CPERM_DENIED)
		ret = CPERM_DENIED;
	else if (errno == ENAMETOOLONG)
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		ret = CMD_NOT_FOUND;
	}
	else
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		ret = SUCCESS;
	}
	return (ret);
}

int	check_enoent(char *cmd)
{
	if (errno == ENOENT)
	{
		if (cmd[0] == '/')
			ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		else
			ft_fprintf(2, "ms: %s: command not found\n", cmd);
		return (CMD_NOT_FOUND);
	}
	return (0);
}

int	check_eacces(char *cmd)
{
	if (errno == EACCES)
	{
		if (cmd[0] == '/')
		{
			errno = EISDIR;
			ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		}
		else
			ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(errno));
		return (CPERM_DENIED);
	}
	return (0);
}
