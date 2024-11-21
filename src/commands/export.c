/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:08:12 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/21 03:46:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int detect_export_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(tokens[0], "export\0", 7) == 0)
	{
		export_handling(ms, tokens, 1);
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
		var_name = ft_strtok(tokens[i], "=");
		value = ft_strtok(NULL, "=");
		if (var_name && value)
		{
			set_env_var(ms, var_name, value);
			printf("Set variable: %s=%s\n", var_name, value);
		}
		else
			printf("minishell: export: %s: not found\n", tokens[i]);
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

	index = find_env_index(ms->test, var_name);
	entry = malloc(ft_strlen(var_name) + ft_strlen(value) + 2);
	if (!entry)
		exit(FAIL);
	ft_strcpy(entry, var_name);
	ft_strcat(entry, "=");
	ft_strcat(entry, value);
	if (index >= 0)
	{
		free(ms->test[index]);
		ms->test[index] = entry;
	}
	else
	{
		env_count = count_env_var(ms->test, 0);
		ms->test = realloc_env(ms->test, env_count + 2);
		ms->test[env_count] = entry;
		ms->test[env_count + 1] = NULL;
	}
}
char **realloc_env(char **env, int new_size)
{
	char **new_env;
	int i;

	i = 0;
	new_env = malloc(new_size * sizeof(char *));
	if (!new_env)
		exit(FAIL);
	while (env && env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	free(env);
	return new_env;
}

void print_env(char **env)
{
	int i = 0;

	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
