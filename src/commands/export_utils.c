/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:30:54 by matislessar       #+#    #+#             */
/*   Updated: 2024/12/02 05:20:15 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**realloc_env(char **env, int new_size)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(new_size, sizeof(char *));
	while (env && env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	free(env);
	return (new_env);
}

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	is_valid_var_name(const char *var_name)
{
	int	i;

	i = 1;
	if (!var_name || !ft_isalpha(var_name[0]))
		return (SUCCESS);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}
