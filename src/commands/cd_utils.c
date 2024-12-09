/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utlis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:35:22 by matislessar       #+#    #+#             */
/*   Updated: 2024/12/06 15:36:11 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Goes to the old pwd when use cd -*/
int	go_old_pwd(t_minishell *ms)
{
	char	*old_pwd;
	
	old_pwd = get_env(ms->env, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("ms: cd: OLDPWD not set\n", 2);
		return (ERROR);
	}
	if (chdir(old_pwd) == -1)
	{
		ft_fprintf(2, "ms: cd: %s: %s\n", old_pwd, strerror(errno));
		return (ERROR);
	}
	ft_putendl_fd(old_pwd, STDOUT_FILENO);
	update_working_directories(ms);
	return (SUCCESS);
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
