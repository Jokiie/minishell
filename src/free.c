
#include "../includes/minishell.h"

void	free_data(t_minishell *ms)
{
	free_at_address(&ms->prompt_name);
	free_at_address(&ms->input);
	free_at_address(&ms->cwd);
	free_int_array(&ms->token.protected);
}

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_at_exit(t_minishell *ms)
{
	free_at_address(&ms->prompt_name);
	free_at_address(&ms->input);
	free_at_address(&ms->cwd);
	free_at_address(&ms->path);
	free_int_array(&ms->token.protected);
	free_tokens_address(&ms->env);
}

void	free_int_array(int **arr)
{
	if (arr && *arr)
	{
		free(*arr);
		*arr = NULL;
	}
}

void	free_at_address(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}