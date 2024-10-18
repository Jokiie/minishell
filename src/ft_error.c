/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:47:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 02:45:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(t_minishell *ms, char *cmd)
{
	if (errno == EACCES)
	{
		ft_fprintf(2, "ms: %s\n", strerror(errno));
		ms->ret = CPERM_DENIED;
	}
	else if (errno == ENOENT)
	{
		ft_fprintf(2, "ms: command not found: %s\n", cmd);
		ms->ret = CMD_NOT_FOUND;
	}
	else
	{
		ft_fprintf(2, "ms: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
}

int	check_error_cd(t_minishell *ms)
{
	if (errno == EACCES)
	{
		ft_fprintf(2, "cd: %s\n", strerror(errno));
		ms->ret = CPERM_DENIED;
	}
	else if (errno == ENOTDIR)
	{
		ft_fprintf(2, "cd: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	else
	{
		ft_fprintf(2, "cd: %s\n", strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
}