/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:41:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 07:10:43 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Call cd , return 0 for success, 1 for errors, CMD_NOT_FOUND if
	cd command is not detected.
*/
int	detect_cd_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(tokens[0], "cd\0", 3) == 0)
		return (cd(ms, tokens));
	return (CMD_NOT_FOUND);
}

/* Change of current working directory */
int	cd(t_minishell *ms, char **tokens)
{
	t_bool	found_dir;
	int		return_value;

	found_dir = FALSE;
	return_value = 0;
	if (!tokens[1] || !*tokens[1])
		return (go_home(ms->env));
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

int	go_home(char **env)
{
	if (chdir(get_env(env, "HOME")) == -1)
		return (ERROR);
	return (SUCCESS);
}
