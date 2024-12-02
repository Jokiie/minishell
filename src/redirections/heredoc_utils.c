/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:07:44 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/02 03:22:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_heredoc_name(t_minishell *ms)
{
	char	*name;
	char	*num;
	char	*full_path;
	int		count;

	count = update_heredoc_number(FALSE);
	num = ft_itoa(count);
	full_path = ft_strjoin(ms->path, "/tmp/heredoc");
	name = ft_strjoin(full_path, num);
	free(full_path);
	free(num);
	return (name);
}

void	check_quotes_delim(t_minishell *ms, int index)
{
	if (ms->token.quoted[index] == 1)
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
		ft_putstr_fd("ms: warning: here-document delimited by end-of-file ", 2);
		ft_fprintf(2, "(wanted '%s')\n", delim);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_delim(char *line, char *delim)
{
	if (ft_strncmp(delim, line, ft_strlen(line)) == 0 && is_same_size(line, delim) == TRUE)
	{
		return (TRUE);
	}
	return (FALSE);
}
