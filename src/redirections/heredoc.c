/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:40:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 15:09:24 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_heredoc_signal;

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_heredoc_signal = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	init_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

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
		ft_fprintf(2, "ms: %s:\n", ms->heredoc.fd_name[i], strerror(errno));
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
	g_heredoc_signal = 0;
	while (1)
	{
		init_heredoc_signals();
		ms->heredoc.input = readline("heredoc> ");
		if (g_heredoc_signal == 1)
		{
			ft_free(ms->heredoc.input);
			ft_free(delim);
			reset_heredoc(ms);
			return (TERM_SIGINT);
		}
		init_signals_noninteractive();
		ms->heredoc.line = expand_line(ms, ms->heredoc.input);
		if (break_check(ms->heredoc.line, delim) == TRUE)
			break ;
		ft_putendl_fd(ms->heredoc.line, fd);
		free_tmp_data(ms);
	}
	free_tmp_data(ms);
	ft_free(delim);
	return (SUCCESS);
}
