/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 02:16:37 by ccodere          ###   ########.fr       */
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

int	execute_heredocs(t_minishell *ms)
{
	int	count;
	int	executed;

	executed = 0;
	count = count_type(ms->tokens, &ms->token.protected, is_heredoc);
	ft_fprintf(2, "%d heredocs to execute\n", count);
	ms->heredoc.count = count;
	ms->heredoc.fd_name = ft_calloc(count + 1, sizeof(char *));
	if (!ms->heredoc.fd_name)
		return (ERROR);
	ms->heredoc.fd_name[count] = NULL;
	while (executed < count)
	{
		ms->ret = exec_heredoc(ms);
		if (g_heredoc_signal == 1)
			return (130);
		executed++;
	}
	if (g_heredoc_signal == 1)
		return (130);
	return (ms->ret);
}

int	exec_heredoc(t_minishell *ms)
{
	int		k;
	char	*delim;

	k = 0;
	while (ms->tokens[k])
	{
		if (is_heredoc(ms->tokens[k]) && ms->token.protected[k] == 0)
		{
			delim = ms->tokens[k + 1];
			check_delim(ms, k + 1);
			if (heredoc(ms, delim) != SUCCESS)
				return (ERROR);
			return (SUCCESS);
		}	
		k++;
	}
	return (SUCCESS);
}

int	heredoc(t_minishell *ms, char *delim)
{
	int	i;
	int	tmp_fd;

	i = update_heredoc_index(FALSE);
	ms->heredoc.fd_name[i] = create_heredoc_name(ms);
	tmp_fd = open(ms->heredoc.fd_name[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		ft_fprintf(2, "Error tmp_fd\n");
		return (ERROR);
	}
	fill_heredoc(ms, tmp_fd, delim);
	close(tmp_fd);
	return (SUCCESS);
}

void	fill_heredoc(t_minishell *ms, int fd, char *delim)
{
	char	*line;
	char	*tmp_line;

	g_heredoc_signal = 0;
	while (g_heredoc_signal == 0)
	{
		init_heredoc_signals();
		line = readline("heredoc> ");
		if (!line || g_heredoc_signal == 1)
		{
			free(line);
			break ;
		}
		init_signals_noninteractive();
		tmp_line = expand_line(ms, line);
		if (check_line(tmp_line, delim) == FALSE)
		{
			free(line);
			free(tmp_line);
			break ;
		}
		ft_putendl_fd(tmp_line, fd);
		free(line);
		free(tmp_line);
	}
	if (g_heredoc_signal == 1)
		ms->ret = 130;
}

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
