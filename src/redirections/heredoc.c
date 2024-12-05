/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:40:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 13:33:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_heredocs(t_minishell *ms)
{
	int	k;

	init_heredoc_data(ms);
	if (init_heredoc_names(ms) == SUCCESS)
	{
		k = 0;
		while (ms->tokens[k])
		{
			while ((is_heredoc(ms->tokens[k]) && ms->token.quoted[k] == 0))
			{
				ms->heredoc.delim = ms->tokens[k + 1];
				check_quotes_delim(ms, k + 1);
				ms->ret = heredoc(ms);
				if (ms->ret != SUCCESS)
					return (ms->ret);
				k += 2;
			}
			if (ms->tokens[k] && ms->tokens[k + 1])
				k++;
			else
				break ;
		}
	}
	return (ms->ret);
}

int	heredoc(t_minishell *ms)
{
	int	i;
	int	fd;

	i = update_heredoc_index(FALSE);
	ms->heredoc.fd_name[i] = create_heredoc_name(ms);
	fd = open(ms->heredoc.fd_name[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_msg(ms->heredoc.fd_name[i], strerror(errno));
		return (ERROR);
	}
	ms->ret = fill_heredoc(ms, fd);
	close(fd);
	return (ms->ret);
}

int	fill_heredoc(t_minishell *ms, int fd)
{
	char	*delim;

	delim = ft_strdup(ms->heredoc.delim);
	while (1)
	{
		init_signals_interactive_heredocs(ms);
		if (ms->received_sig == SIGINT)
		{
			free_ptr(ms->heredoc.input);
			free_ptr(delim);
			reset_heredoc(ms);
			return (TERM_SIGINT);
		}
		ms->heredoc.input = readline("heredoc> ");
		init_signals_noninteractive();
		ms->heredoc.line = expand_line(ms, ms->heredoc.input, delim);
		if (break_check(ms->heredoc.line, delim) == TRUE)
			break ;
		ft_putendl_fd(ms->heredoc.line, fd);
		free_tmp_data(ms);
	}
	free_tmp_data(ms);
	free_ptr(delim);
	return (SUCCESS);
}
