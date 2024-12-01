/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/01 01:59:57 by ccodere          ###   ########.fr       */
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
	else if (errno == ENOENT || errno == ENAMETOOLONG)
		ret = check_enoent(cmd);
	else if (errno == EACCES)
		ret = check_eacces(cmd);
	else
	{
		errno = ENOENT;
		error_msg(cmd, strerror(errno));
		ret = CMD_NOT_FOUND;
	}
	return (ret);
}

int	check_enoent(char *cmd)
{
	if (cmd[0] == '/')
		error_msg(cmd, strerror(errno));
	else
		error_msg(cmd, "command not found");
	return (CMD_NOT_FOUND);
}

int	check_eacces(char *cmd)
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

void	error_msg(char *cmd, char *msg)
{
	char	*name;
	char	*sep;
	char	*newl;
	char	buffer[SIZE_BUF];
	int		size;
	
	name = "ms: ";
	sep = ": ";
	newl = "\n";
	ft_bzero(buffer, SIZE_BUF);
	ft_strcpy(buffer, name);
	ft_strlcat(buffer, cmd, (SIZE_BUF - 96));
	ft_strcat(buffer, sep);
	ft_strcat(buffer, msg);
	ft_strcat(buffer, newl);
	size = ft_strlen(buffer);
	write(2, buffer, size);
}
