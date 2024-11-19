/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:04:16 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/18 23:59:38 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_heredoc(t_minishell *ms)
{
	unlink_heredocs(ms);
	clear_heredoc_names(ms);
	reset_heredoc_statics();
}

void	unlink_heredocs(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < 42 && ms->heredoc.fd_name[i] != NULL)
	{
		if (unlink(ms->heredoc.fd_name[i]) != 0)
			ft_fprintf(2, "ms: unlink failed for %s\n", ms->heredoc.fd_name[i]);
		i++;
	}
}

void	clear_heredoc_names(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < 42 && ms->heredoc.fd_name[i] != NULL)
	{
		free(ms->heredoc.fd_name[i]);
		ms->heredoc.fd_name[i] = NULL;
		i++;
	}
}