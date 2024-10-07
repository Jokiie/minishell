/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/07 03:36:22 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Check if a token contains a redirection character. If so, execute the function
that redirects input for '<' and output for '>' using the next token, which
should be a file name. After breaking the loop, a new list of tokens is created
without the "<>" characters, allowing the command to be executed. Before this,
the command couldn't execute because it attempted to interpret "<>" as if it
were a command or an argument to a command.
*/
void	ft_exec_redirection(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->tokens[i])
	{
		if (ft_strncmp(ms->tokens[i], ">", 1) == 0)
		{
			redirect_output(ms, ms->tokens[i + 1]);
			break ;
		}
		else if (ft_strncmp(ms->tokens[i], "<", 1) == 0)
		{
			redirect_input(ms, ms->tokens[i + 1]);
			break ;
		}
		i++;
	}
	ft_recreate_tokens(ms, i);
}

/*
Recreate the tokens list without the redirection characters, as explained above.
I removed the ft_free_tokens call because it corrupt the list. I didn't find leaks,
to verify later.
*/
void	ft_recreate_tokens(t_minishell *ms, int i)
{
	char	**new_tokens;
	int		k;

	new_tokens = (char **)malloc(sizeof(char *) * (i + 1));
	k = 0;
	while (k < i)
	{
		if ((ft_strncmp(ms->tokens[k], ">", 1) != 0)
			&& (ft_strncmp(ms->tokens[k], "<", 1) != 0))
			new_tokens[k] = ms->tokens[k];
		k++;
	}
	new_tokens[k] = NULL;
	ms->tokens = new_tokens;
}
/*
< : redirect input.
I think input is set back to stdin after closing the file (fdin) but I'm not sure.
*/
void	redirect_input(t_minishell *ms, char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "ms: %s: No such file or directory\n", file);
		exit(EXIT_FAILURE);
	}
	dup2(fdin, ms->std_in);
	close(fdin);
}

/*
> : redirect output.
I think output is set back to stdout after closing the file (fdout) but i'm not sure.
*/
void	redirect_output(t_minishell *ms, char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		return ;
	}
	dup2(fdout, ms->std_out);
	close(fdout);
}
