
#include "../includes/minishell.h"

void	free_data(t_minishell *ms)
{
	free_at_adress(&ms->prompt_name);
	free_at_adress(&ms->input);
	free_at_adress(&ms->cwd);
	ft_free(ms->token.protected);
	reset_heredoc(ms);
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
	ft_free(ms->prompt_name);
	ft_free(ms->input);
	ft_free(ms->cwd);
	ft_free(ms->path);
	free(ms->token.protected);
	free_tokens(ms->env);
}

void	free_at_adress(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			ft_free(tokens[i]);
			i++;
		}
		free(tokens);
		tokens = NULL;
	}
}
