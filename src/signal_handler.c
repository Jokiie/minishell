/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:35:57 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/03 02:24:31 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	ctrl-D -> quit the shell (if (!ms->input), in execms)
	ctrl-C -> display a new prompt on a new line
				(send a SIGINT to the current executing process)
	ctrl-\ -> is ignored
	ps : Children processes inherit the signal handler so there is no need to
		call it in the "if (pid == 0)"
*/
volatile sig_atomic_t	g_sig_received = 0;

void	init_signals_interactive(t_minishell *ms)
{
	struct sigaction	sa;

	ms->received_sig = g_sig_received;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sync_signals(t_minishell *ms)
{
	ms->received_sig = g_sig_received;
	if (ms->received_sig != 0)
		ms->ret = 128 + ms->received_sig;
	g_sig_received = 0;
}

void	handle_sigint(int sig)
{
	g_sig_received = sig;
	if (g_sig_received == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
}

void	init_signals_interactive_heredocs(t_minishell *ms)
{
	struct sigaction	sa;

	ms->received_sig = g_sig_received;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_sigint_hd;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_hd(int sig)
{
	g_sig_received = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
