/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/20 13:05:33 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(t_minishell *ms, char *cmd)
{
	if (errno == EISDIR)
	{
		ft_fprintf(2, "ms: %s: %s\n", cmd, strerror(EACCES));
		ms->ret = CPERM_DENIED;
	}
	else if (errno == EACCES)
	{
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), cmd);
		ms->ret = CPERM_DENIED;
	}
	else if (errno == ENOENT)
	{
		ft_fprintf(2, "ms: %s: command not found\n", cmd);
		ms->ret = CMD_NOT_FOUND;
	}
	else if (errno == ENAMETOOLONG)
	{
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), cmd);
		ms->ret = CMD_NOT_FOUND;
	}
	else
	{
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), cmd);
		ms->ret = ERROR;
	}
	return (ms->ret);
}
