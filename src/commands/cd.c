/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/24 03:18:29 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Call cd , return 0 for success, 1 for errors, CMD_NOT_FOUND if
	cd command is not detected.
*/
int	detect_cd_call(char **tokens)
{
	int	return_value;

	return_value = 0;
	if (ft_strncmp(tokens[0], "cd\0", 3) == 0)
		return_value = cd(tokens);
	else
		return_value = CMD_NOT_FOUND;
	return (return_value);
}

/* Change of current working directory */
int	cd(char **tokens)
{
	t_bool	found_dir;
	int		return_value;

	found_dir = FALSE;
	return_value = 0;
	if (!tokens[1] || !*tokens[1])
	{
		if (chdir(getenv("HOME")) != -1)
			return (return_value);
		else
			return (ERROR);
	}
	else if (tokens[2])
	{
		ft_putstr_fd("ms: cd: too many arguments\n", 2);
		return_value = ERROR;
	}
	else if (return_value != ERROR && chdir(tokens[1]) == 0)
	{
		found_dir = TRUE;
		return_value = SUCCESS;
	}
	else if (found_dir == FALSE)
	{
		ft_fprintf(2, "ms: cd: %s: %s\n", tokens[1], strerror(errno));
		return_value = ERROR;
	}
	return (return_value);
}
