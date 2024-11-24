#include "../../includes/minishell.h"

static char	**realloc_env_vars(t_minishell *ms, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (ms->env[i] && i < size)
	{
		new_env[i] = ft_strdup(ms->env[i]);
		free_ptr(ms->env[i]);
		i++;
	}
	free(ms->env);
	return (new_env);
}

int	detect_unset_call(t_minishell *ms, char **tokens)
{
	if (ft_strncmp(tokens[0], "unset\0", 6) == 0)
	{
		unset_handling(ms, tokens, 1);
		ms->ret = SUCCESS;
		return (ms->ret);
	}
	ms->ret = CMD_NOT_FOUND;
	return (ms->ret);
}
void	unset_handling(t_minishell *ms, char **tokens, int i)
{
	int	env_index;

	while (tokens[i])
	{
		env_index = find_env_index(ms->env, tokens[i]);
		if (env_index >= 0)
		{
			remove_env_var1(ms, env_index);
			printf("Unset variable: %s\n", tokens[i]);
		}
		else
			printf("minishell: unset: %s: not found\n", tokens[i]);
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

bool	remove_env_var1(t_minishell *ms, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(ms->env))
		return (false);
	free_ptr(ms->env[idx]);
	i = idx;
	count = idx;
	while (ms->env[i + 1])
	{
		ms->env[i] = ft_strdup(ms->env[i + 1]);
		free_ptr(ms->env[i + 1]);
		count++;
		i++;
	}
	ms->env = realloc_env_vars(ms, count);
	if (!ms->env)
		return (false);
	return (true);
}

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
