/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:42:06 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 02:09:44 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Iter in each token and execute the adequate function for each redirection.
	A new list of tokens is created	without the redirections characters,
	allowing the command to be executed. Before this, the command couldn't be
	executed because it attempted to interpret '<<', '>>', '<', and '>' as if
	it were a command or an argument to a command. Return 0 if successful or 1
	for failure.
*/
int	exec_redirections(t_minishell *ms, char **tok, int **quoted, int **expanded)
{
	int	k;

	k = 0;
	while (tok[k])
	{
		if (is_heredoc(tok[k]) && (*quoted)[k] == 0 && (*expanded)[k] == 0)
		{
			if (redirect_heredocs(ms) != SUCCESS)
				return (ERROR);
			k += 2;
		}
		else if (is_redirect(tok[k]) && (*quoted)[k] == 0
			&& (*expanded)[k] == 0)
		{
			if (redirect(tok[k], tok[k + 1]))
				return (ERROR);
			k += 2;
		}
		else
			k++;
	}
	remake_tokens(ms, tok, quoted, expanded);
	return (SUCCESS);
}

int	redirect(char *tokens, char *file)
{
	int	ret;

	ret = 0;
	if (is_append(tokens))
		ret = append_output(file);
	else if (is_redirect_out(tokens))
		ret = redirect_output(file);
	else if (is_redirect_in(tokens))
		ret = redirect_input(file);
	return (ret);
}
