/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:07:44 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/18 23:59:28 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_heredoc(t_minishell *ms)
{
	int	k;
	int	count;

	count = 0;
	k = 0;
	while (ms->tokens[k])
	{
		if (is_heredoc(ms->tokens[k]) && ms->token.protected[k] == 0)
			count++;
		k++;
	}
	return (count);
}

void	check_delim(t_minishell *ms, int pos)
{
	if (ms->token.protected[pos] == TRUE)
		ms->heredoc.in_quotes = TRUE;
	else
		ms->heredoc.in_quotes = FALSE;
}

t_bool	check_line(char *line, char *delim)
{
	if (!line || ft_strcmp(line, delim) == 0)
	{
		if (!line)
			ft_fprintf(2,
				"ms: warning: here-document delimited by end-of-file (wanted '%s')\n",
				delim);
		free(line);
		return (FALSE);
	}
	return (TRUE);
}
