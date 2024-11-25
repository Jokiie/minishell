/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 16:20:33 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *cmd)
{
	int	ret;

	ret = 0;
	if (errno == EISDIR)
	{
		error_msg(cmd, strerror(errno));
		ret = CPERM_DENIED;
	}
	else if (check_enoent(cmd) == CMD_NOT_FOUND)
		ret = CMD_NOT_FOUND;
	else if (check_eacces(cmd) == CPERM_DENIED)
		ret = CPERM_DENIED;
	else if (errno == ENAMETOOLONG)
	{
		error_msg(cmd, strerror(errno));
		ret = CMD_NOT_FOUND;
	}
	else
	{
		error_msg(cmd, strerror(errno));
		ret = ERROR;
	}
	return (ret);
}

int	check_enoent(char *cmd)
{
	if (errno == ENOENT)
	{
		if (cmd[0] == '/')
			error_msg(cmd, strerror(errno));
		else
			error_msg(cmd, "command not found");
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
			error_msg(cmd, strerror(errno));
		}
		else
			error_msg(cmd, strerror(errno));
		return (CPERM_DENIED);
	}
	return (0);
}

void	error_msg(char *cmd, char *msg)
{
	char	*name;
	char	*sep;
	char	*newl;
	char	buffer[512];

	name = "ms: ";
	sep = ": ";
	newl = "\n";
	ft_strcpy(buffer, name);
	ft_strcat(buffer, cmd);
	ft_strcat(buffer, sep);
	ft_strcat(buffer, msg);
	ft_strcat(buffer, newl);
	write(2, buffer, ft_strlen(buffer));
}
