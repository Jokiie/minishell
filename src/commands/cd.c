/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:41:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 05:28:30 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Call cd , return 0 for success, 1 for errors, CMD_NOT_FOUND if
	cd command is not detected.*/
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
		return (go_home(ms));
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
	char	*home;

	home = get_env(ms->env, "HOME");
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
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		cwd = ft_strdup("deleted_dir");
	}
	if (ms->cwd)
		set_env_var(ms, "OLDPWD", ms->cwd);
	else
		set_env_var(ms, "OLDPWD", "deleted_dir");
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
