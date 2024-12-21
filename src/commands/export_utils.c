/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:30:54 by matislessar       #+#    #+#             */
/*   Updated: 2024/12/21 00:55:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Realloc the momory of the env var*/
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

/*Check if the name of the var is OK*/
int	is_valid_var_name(const char *var_name)
{
	int		i;
	size_t	len;

	i = 1;
	len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "=", len))
		return (ERROR);
	if (!var_name || (!ft_isalpha(var_name[0]) && var_name[0] != '_'))
		return (SUCCESS);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

/*Finds the var name*/
char	*extract_var_name(const char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

/*Finds the value of the var*/
char	*extract_var_value(const char *str, int j)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	value = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		value[j++] = str[i];
		i++;
	}
	value[j] = '\0';
	return (value);
}

void	export_handling_x(t_minishell *ms, char **tokens, int i)
{
	if (!tokens[i])
	{
		export_declare_x(ms->env);
		return ;
	}
}
