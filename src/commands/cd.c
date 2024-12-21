/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:41:58 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/21 00:50:58 by ccodere          ###   ########.fr       */
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
	if (!tokens[1] || !*tokens[1] || ft_strcmp(tokens[1], "~") == 0)
		return (go_home(ms));
	else if (ft_strcmp(tokens[1], "-") == 0)
		return (go_old_pwd(ms));
	else if (ft_strcmp(tokens[1], "--") == 0)
		return (go_home(ms));
	else if (tokens[2])
		return (SUCCESS);
	return (change_directory(ms, tokens[1]));
}

/* Update cwd and OLDPWD in both struct and environment variables */
void	update_working_directories(t_minishell *ms)
{
	char	*saved_old;

	saved_old = ft_strdup(ms->cwd);
	if (saved_old)
		ms->prev_cwd = saved_old;
	set_env_var(ms, "OLDPWD", ms->prev_cwd);
	free_ptr(saved_old);
	free_at_address(&ms->cwd);
	ms->cwd = getcwd(NULL, 0);
	if (!ms->cwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories:", 2);
		ft_putendl_fd("No such file or directory\n", 2);
	}
	set_env_var(ms, "PWD", ms->cwd);
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
