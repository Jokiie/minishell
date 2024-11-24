/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:07:44 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/24 09:35:34 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_quotes_delim(t_minishell *ms, int index)
{
	if (ms->token.protected[index] == 1)
	{
		ms->heredoc.in_quotes = TRUE;
	}
	else
	{	
		ms->heredoc.in_quotes = FALSE;
	}
}

t_bool	break_check(char *line, char *delim)
{
	if (line_is_null(line, delim) == TRUE || is_delim(line, delim) == TRUE)
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	line_is_null(char *line, char *delim)
{
	if (!line)
	{
		ft_fprintf(2, "\nms: warning: here-document delimited by end-of-file (wanted '%s')\n", delim);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_delim(char *line, char *delim)
{
	if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
	{
		return (TRUE);
	}
	return (FALSE);
}
