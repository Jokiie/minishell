/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:08:12 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/13 19:28:57 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int detect_export_call(t_minishell *ms, int k)
{
	if ((k == 0) && ft_strncmp(ms->tokens[k], "export", 7) == 0)
	{
		export_handling(ms, 1);
		ms->ret = SUCCESS;
		return (ms->ret);
	}
	ms->ret = CMD_NOT_FOUND;
	return (ms->ret);
}

void	export_handling(t_minishell *ms, int i)
{
	char	*var_name;
	char	*value;
	
	while (ms->tokens[i])
	{
		var_name = ft_strtok(ms->tokens[i], "=");
		value = ft_strtok(NULL, "=");
		if (var_name && value)
		{
			set_env_var(ms, var_name, value);
			printf("Set variable: %s=%s\n", var_name, value);
		}
		else
			printf("minishell: export: %s: not found\n", ms->tokens[i]);
		i++;
	}
}

int	count_env_var(char **env, int count)
{
	while (env[count])
		count++;
	return (count);
}

void	set_env_var(t_minishell *ms, const char *var_name, const char *value)
{
	char	*entry;
	int		index;
	int		env_count;

	index = find_env_index(ms->env, var_name);
	entry = malloc(ft_strlen(var_name) + ft_strlen(value) + 2);
	if (!entry)
		exit(FAIL);
	printf("%s=%s\n", var_name, value);
	if (index >= 0)
	{
		free(ms->env[index]);
		ms->env[index] = entry;
	}
	else
	{
		env_count = count_env_var(ms->env, 0);
		ms->env[env_count] = entry;
		ms->env[env_count + 1] = NULL;
	}
}
