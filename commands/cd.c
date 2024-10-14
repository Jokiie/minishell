/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/14 12:43:24 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	detect_cd_call(t_minishell *ms)
{
	if (ft_strnstr(ms->tokens[0], "cd", 2))
	{
		cd(ms->tokens);
		return (SUCCESS);
	}
	return (FAIL);
}

/* Change of current working directory */
void	cd(char **tokens)
{
	t_bool	found_dir;

	found_dir = FALSE;
	if (!tokens[1])
	{
		ft_fprintf(2, "cd: need a relative or absolute path\n");
		return ;
	}
	if (tokens[2])
	{
		ft_fprintf(2, "cd: string not in pwd: %s\n", tokens[1]);
		return ;
	}
	if (chdir(tokens[1]) == 0)
		found_dir = TRUE;
	else if (found_dir == FALSE)
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", tokens[1]);
		return ;
	}
}
