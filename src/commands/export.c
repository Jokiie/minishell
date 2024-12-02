/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:08:12 by matislessar       #+#    #+#             */
/*   Updated: 2024/12/02 17:26:57 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	detect_export_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(tokens[0], "export\0", 7) == 0)
	{
		export_handling(ms, tokens, 1);
		if (ms->ret == ERROR)
			return (ERROR);
		else
			return (SUCCESS);
	}
	return (CMD_NOT_FOUND);
}

void	export_handling(t_minishell *ms, char **tokens, int i)
{
	char	*var_name;
	char	*value;

	while (tokens[i])
	{
		var_name = extract_var_name(tokens[i]);
		value = extract_var_value(tokens[i], 0);

		if (!is_valid_var_name(var_name))
		{
			ft_fprintf(2, "ms: export: %s: not a valid identifier\n", tokens[i]);
			ms->ret = ERROR;
		}
		else if (var_name && value)
			set_env_var(ms, var_name, value);
		else
			ms->ret = SUCCESS;
		free_ptr(var_name);
		free_ptr(value);
		i++;
	}
}

void	set_env_var(t_minishell *ms, const char *var_name, const char *value)
{
	char	*entry;
	int		index;
	int		env_count;

	index = find_env_index(ms->env, var_name);
	entry = ft_calloc(ft_strlen(var_name) + ft_strlen(value) + 2, sizeof(char));
	ft_strcpy(entry, var_name);
	ft_strcat(entry, "=");
	if (value)
		ft_strcat(entry, value);
	if (index >= 0)
	{
		free_ptr(ms->env[index]);
		ms->env[index] = entry;
	}
	else
	{
		env_count = env_var_count(ms->env);
		ms->env = realloc_env(ms->env, env_count + 2);
		ms->env[env_count] = entry;
		ms->env[env_count + 1] = NULL;
	}
}
