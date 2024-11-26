/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:41:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/26 17:03:14 by matislessar      ###   ########.fr       */
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

/* Change the current working directory */
int	cd(t_minishell *ms, char **tokens)
{
	if (!tokens[1] || !*tokens[1])
	{
		ft_putstr_fd("ms: cd: no directory specified\n", 2);
		return (ERROR);
	}
	else if (tokens[2])
	{
		ft_putstr_fd("ms: cd: too many arguments\n", 2);
		return (ERROR);
	}
	return (change_directory(ms, tokens[1]));
}

/* Navigate to the home directory */
int	go_home(t_minishell *ms)
{
	char *home = get_env(ms->env, "HOME");
	if (!home || chdir(home) == -1)
	{
		ft_putstr_fd("ms: cd: HOME not set or inaccessible\n", 2);
		return (ERROR);
	}
	update_working_directories(ms);
	return (SUCCESS);
}

/* Update cwd and OLDPWD in both struct and environment variables */
void	update_working_directories(t_minishell *ms)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return;
	}
	set_env_var(ms, "OLDPWD", get_env(ms->env, "PWD"));
	set_env_var(ms, "PWD", cwd);
	if (ms->prev_cwd)
		free(ms->prev_cwd);
	ms->prev_cwd = ms->cwd;
	set_env_var(ms, "PWD", cwd);
	ms->cwd = cwd;
}

/* Change directory and update working directories */
int	change_directory(t_minishell *ms, const char *path)
{
	if (chdir(path) == -1)
	{
		ft_fprintf(2, "ms: cd: %s: %s\n", path, strerror(errno));
		return (ERROR);
	}
	update_working_directories(ms);
	return (SUCCESS);
}
