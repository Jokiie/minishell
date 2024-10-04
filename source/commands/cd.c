/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 12:55:22 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **args)
{
	char *home;
	t_bool found_dir;

	found_dir = FALSE;
	if (args[2])
	{
		ft_fprintf(2, "cd: string not in pwd: %s\n", args[1]);
		return ;
	}
	if (chdir(args[1]) == 0)
		found_dir = TRUE;
	else if (args[1] == NULL)
	{
		home = getenv("HOME");
		chdir(home);
	}
	else if (found_dir == FALSE)
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", args[1]);
		return ;
	}
}
