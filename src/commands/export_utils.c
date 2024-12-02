/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:30:54 by matislessar       #+#    #+#             */
/*   Updated: 2024/12/02 16:46:09 by matislessar      ###   ########.fr       */
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

int	is_valid_var_name(const char *var_name)
{
	int	i;
	size_t	len;

	i = 1;
	len = ft_strlen(var_name);
	if (!ft_strncmp(var_name, "=", len))
		return (ERROR);
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

char	*extract_var_value(const char *str, int j)
{
	int		i;
	char	quote;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	quote = 0;
	value = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			value[j++] = str[i];
		i++;
	}
	value[j] = '\0';
	return (value);
}
