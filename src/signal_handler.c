/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:35:57 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/30 13:22:42 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_received = 0;
/*
	ctrl-D -> quit the shell (if (!ms->input), in execms)
	ctrl-C -> display a new prompt on a new line
				(send a SIGINT to the current executing process)
	ctrl-\ -> is ignored
	ps : Children processes inherit the signal handler so there is no need to
		call it in the "if (pid == 0)"
*/
void	init_signals_interactive(t_minishell *ms)
{
	struct sigaction	sa;

	ms->received_sig = g_sig_received;
	handle_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &reset_prompt;
	sigaction(SIGINT, &sa, NULL);
}

void	init_signals_interactive_heredocs(t_minishell *ms)
{
	struct sigaction	sa;

	ms->received_sig = g_sig_received;
	handle_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &reset_prompt2;
	sigaction(SIGINT, &sa, NULL);
}

void	sync_signals(t_minishell *ms)
{
	ms->received_sig = g_sig_received;
	g_sig_received = 0;
}

void	reset_prompt(int sig)
{
	g_sig_received = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_sig_received)
		write(1, "\n", 1);
	else
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//write(1, "\n", 1);
	// rl_redisplay();
}
void	reset_prompt2(int sig)
{
	g_sig_received = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// write(1, "\n", 1);
	// rl_redisplay();
}
