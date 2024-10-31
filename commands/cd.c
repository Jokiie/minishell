/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/31 03:47:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
	Call cd , return 0 for success, 1 for errors, CMD_NOT_FOUND if
	cd command is not detected.
*/
int	detect_cd_call(t_minishell *ms, int k)
{
	if ((k == 0) && ft_strncmp(ms->tokens[k], "cd\0", 3) == 0)
	{
		ms->ret = cd(ms, k);
	}
	else
	{
		ms->ret = CMD_NOT_FOUND;
	}
	return (ms->ret);
}

/* Change of current working directory */
int	cd(t_minishell *ms, int k)
{
	t_bool	found_dir;

	found_dir = FALSE;
	if (ms->cwd)
		ms->prev_cwd = ft_strdup(ms->cwd);
	if (!ms->tokens[k + 1] || *(ms->tokens[k + 1]) == '\0')
	{
		ft_fprintf(2, "ms: cd: need a relative or absolute path\n");
		ms->ret = ERROR;
	}
	else if (ms->tokens[k + 2])
	{
		ft_fprintf(2, "ms: cd: too many arguments\n");
		ms->ret = ERROR;
	}
	else if (ms->ret != ERROR && chdir(ms->tokens[k + 1]) == 0)
	{
		found_dir = TRUE;
		ms->ret = SUCCESS;
	}
	else if (found_dir == FALSE)
	{
		ft_fprintf(2, "ms: cd: %s: %s\n", ms->tokens[k + 1], strerror(errno));
		ms->ret = ERROR;
	}
	return (ms->ret);
}
