/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:04:16 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 02:11:37 by ccodere          ###   ########.fr       */
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
	if (!ms->heredoc.fd_name)
		return ;
	while (ms->heredoc.fd_name[i] != NULL)
	{
		if (unlink(ms->heredoc.fd_name[i]) != 0)
			error_msg(ms->heredoc.fd_name[i], "unlink failed");
		i++;
	}
}

void	clear_heredoc_names(t_minishell *ms)
{
	if (!ms->heredoc.fd_name)
		return ;
	free_tokens(ms->heredoc.fd_name);
	ms->heredoc.fd_name = NULL;
}

void	free_tmp_data(t_minishell *ms)
{
	free_at_address(&ms->heredoc.line);
	free_at_address(&ms->heredoc.input);
}

int	init_heredoc_names(t_minishell *ms)
{
	int	count;

	count = count_type(ms->tokens, &ms->token.quoted, &ms->token.expanded,
			is_heredoc);
	ms->heredoc.count = count;
	ms->heredoc.fd_name = ft_calloc(count + 1, sizeof(char *));
	if (!ms->heredoc.fd_name)
	{
		free(ms->heredoc.fd_name);
		ms->ret = ERROR;
		return (ERROR);
	}
	ms->heredoc.fd_name[count] = NULL;
	return (SUCCESS);
}
