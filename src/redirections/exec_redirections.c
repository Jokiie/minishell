/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:08:33 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/19 06:24:37 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Execute the adequate function for each redirection. A new list of tokens is
	created	without the redirections characters, allowing the command to be
	executed. Before this, the command couldn't execute because it attempted to
	interpret '<<', '>>', '<', and '>' as if it were a command or an argument
	to a command.
*/
int	exec_redirections(t_minishell *ms)
{
	static int	i = 0;
	int			k;
	int			return_value;
	int			count;

	return_value = 0;
	k = 0;
	//ft_fprintf(2, "Before redirection\n");
	//print_debug(ms->tokens);
	while (ms->tokens[k])
	{
		if ((is_heredoc(ms->tokens[k]) || is_redirect(ms->tokens[k])) && ms->token.protected[k] == 0)
		{
			return_value = redirect(ms, return_value, k, &i);
			k += 2;
		}
		else
			k++;
		if (return_value == FAIL || return_value == FAIL)
			return (ERROR);
	}
	count = count_tokens_left(ms);
	//ft_fprintf(2, "count = %d\n", count);
	recreate_tokens(ms, count);
	//ft_fprintf(2, "After redirection\n");
	//print_debug(ms->tokens);
	i = 0;
	return (return_value);
}
