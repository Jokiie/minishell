/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:07:44 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 04:24:09 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_delim(t_minishell *ms, int pos)
{
	if (!ms->tokens[pos])
		return ;
	if (ms->token.protected[pos] == TRUE)
		ms->heredoc.in_quotes = TRUE;
	else
		ms->heredoc.in_quotes = FALSE;
}

t_bool	check_line(char *line, char *delim)
{
	if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
	{
		if (!line)
			ft_fprintf(2, "ms: warning: here-document delimited by end-of-file (wanted '%s')\n", delim);
		return (FALSE);
	}
	return (TRUE);
}
