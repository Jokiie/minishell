/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/15 15:46:06 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_exec_redirection(t_minishell *ms)
{
	int	k;

	k = 0;
	while (ms->tokens[k])
	{
		if (ft_strncmp(ms->tokens[k], ">", 1) == 0)
		{
			redirect_output(ms, ms->tokens[k + 1]);
			break ;
		}
		else if (ft_strncmp(ms->tokens[k], "<", 1) == 0)
		{
			redirect_input(ms, ms->tokens[k + 1]);
			break ;
		}
		k++;
	}
	ft_recreate_tokens(ms, k);
}

/*
	Recreate the tokens list without the redirection characters,
	as explained above.
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

/* < : redirect input. */
void	redirect_input(t_minishell *ms, char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "ms: No such file or directory near '<'\n");
		exit(EXIT_FAILURE);
	}
	dup2(fdin, ms->std_in);
	close(fdin);
}

/* > : redirect output. */
void	redirect_output(t_minishell *ms, char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0)
	{
		ft_fprintf(2, "ms: No such file or directory near '>'\n", file);
		return ;
	}
	dup2(fdout, ms->std_out);
	close(fdout);
}
