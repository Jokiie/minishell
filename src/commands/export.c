/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:08:12 by matislessar       #+#    #+#             */
/*   Updated: 2024/12/05 13:34:33 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*Call export , return 0 for success, 1 for errors, CMD_NOT_FOUND if
	cd command is not detected.*/
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
	else if (ft_strncmp(tokens[0], "export=\0", 8) == 0)
		return (SUCCESS);
	return (CMD_NOT_FOUND);
}

void	export_declare_x(char **env)
{
	int i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], STDOUT_FILENO);
			if (env[i][j] == '=')
			{
				ft_putchar_fd('"', STDOUT_FILENO);
				ft_putstr_fd(env[i] + j + 1, STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
				break;
			}
			j++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}
		// for (int j = 0; env[i][j]; j++)

/*Count the nomber of var in the env*/
int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

void	export_handling(t_minishell *ms, char **tokens, int i)
{
	char	*var_name;
	char	*value;
	
	export_handling_x(ms, tokens, i);
	while (tokens[i])
	{
		var_name = extract_var_name(tokens[i]);
		value = extract_var_value(tokens[i], 0);
		if (tokens[i][0] == '\0' && ms->token.quoted[i] == 1)
			ft_fprintf(2, "ms: export: not valid in this context: %s\n", tokens[i]);
		if (!is_valid_var_name(var_name))
		{
			ft_fprintf(2, "ms: export: not valid in this context: %s\n", tokens[i]);
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
