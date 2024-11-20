/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:28:23 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/20 15:48:57 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	detect_unset_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(tokens[0], "unset\0", 6) == 0)
	{
		unset_handling(ms, 1);
		ms->ret = SUCCESS;
		return (ms->ret);
	}
	ms->ret = CMD_NOT_FOUND;
	return (ms->ret);
}
void	unset_handling(t_minishell *ms, int i)
{
	int	env_index;

	while (ms->tokens[i])
	{
		env_index = find_env_index(ms->env, ms->tokens[i]);
		if (env_index >= 0)
		{
			remove_env_var(ms->env, env_index);
			printf("Unset variable: %s\n", ms->tokens[i]);
		}
		else
			printf("minishell: unset: %s: not found\n", ms->tokens[i]);
		i++;
	}
}

int	find_env_index(char **env, const char *var_name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (FAIL);
}

void	remove_env_var(char **env, int index)
{
	while(env[index])
		env[index] = env[index + 1];
	index++;
}
