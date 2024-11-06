
#include "../includes/minishell.h"

/*
	Check if a token contains a redirection character. If so, execute the
	function that redirects input for '<' and output for '>' using the next
	token, which should be a file name. After breaking the loop, a new list
	of tokens is created without the "<>" characters, allowing the command
	to be executed. Before this, the command couldn't execute because it
	attempted to interpret "<>" as if it were a command or an argument to
	a command.
*/
int	exec_redirection(t_minishell *ms)
{
	int	k;

	k = 0;
	if (!ms->tokens || !*(ms->tokens))
		return ERROR;
	while (ms->tokens[k])
	{
		if (is_append(ms->tokens[k]))
		{
			ms->ret = append_output(ms, ms->tokens[k + 1]);
			break ;
		}
		else if (is_redirect_out(ms->tokens[k]))
		{
			ms->ret = redirect_output(ms, ms->tokens[k + 1]);
			break ;
		}
		else if (is_redirect_in(ms->tokens[k]))
		{
			ms->ret = redirect_input(ms, ms->tokens[k + 1]);
			break ;
		}
		k++;
	}
	recreate_tokens(ms, k);
	return (ms->ret);
}

/*
	Recreate the tokens list without the redirection characters,
	as explained above.
*/
void	recreate_tokens(t_minishell *ms, int i)
{
	char	**new_tokens;
	int		k;

	new_tokens = (char **)malloc(sizeof(char *) * (i + 1));
	k = 0;
	while (k < i)
	{
		if (!is_redirect(ms->tokens[k]))
			new_tokens[k] = ms->tokens[k];
		k++;
	}
	new_tokens[k] = NULL;
	ms->tokens = new_tokens;
}

/* < : redirect input in the specified file */
int	redirect_input(t_minishell *ms, char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ms->ret = ERROR;
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
	}
	else
	{
		dup2(fdin, ms->std_in);
		close(fdin);
		ms->ret = SUCCESS;
	}
	return (ms->ret);
}

/* > : redirect output in the specified file */
int	redirect_output(t_minishell *ms, char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fdout < 0)
	{
		ms->ret = ERROR;
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
	}
	else
	{
		dup2(fdout, ms->std_out);
		close(fdout);
		ms->ret = SUCCESS;
	}
	return (ms->ret);
}

/* Append output obtained in the specified file */
int	append_output(t_minishell *ms, char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fdout < 0)
	{
		ms->ret = ERROR;
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
	}
	else
	{
		dup2(fdout, ms->std_out);
		close(fdout);
		ms->ret = SUCCESS;
	}
	return (ms->ret);
}
