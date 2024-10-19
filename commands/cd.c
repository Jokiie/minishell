/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/19 12:06:20 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	detect_cd_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(ms->tokens[0], "cd\0", 3) == 0)
	{
		ms->ret = cd(ms, tokens);
		return (ms->ret);
	}
	ms->ret = CMD_NOT_FOUND;
	return (CMD_NOT_FOUND);
}

/* Change of current working directory */
int	cd(t_minishell *ms, char **tokens)
{
	t_bool	found_dir;

	found_dir = FALSE;
    if (!ms->tokens[1] || *(ms->tokens[1]) == '\0')
	{
		ft_fprintf(2, "ms: cd: need a relative or absolute path\n");
        ms->ret = ERROR;
		return (ERROR);
    }
	else if (ms->tokens[2])
	{
		ft_fprintf(2, "ms: cd: too many arguments\n");
		ms->ret = ERROR;
		return (ERROR);
	}
	if (chdir(tokens[1]) == 0)
	{
		found_dir = TRUE;
		ms->ret = SUCCESS;
	}
	else if (found_dir == FALSE)
		ms->ret = check_error_cd(ms);
	return (ms->ret);
}
