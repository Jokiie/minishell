/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:21:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/20 21:54:15 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	ctrl-D -> quit the shell (if (!ms->input), in execms)
	ctrl-C -> display a new prompt on a new line
				(send a SIGINT to the current executing process)
	ctrl-\ -> do nothing
	ps : Children processes inherit the signal handler so there is no need to
		call it in the "if (pid == 0)"
*/
void	ft_init_sigaction(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	ft_memset(&sa_sigquit, 0, sizeof(sa_sigquit));
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
	ft_memset(&sa_sigint, 0, sizeof(sa_sigint));
	sa_sigint.sa_sigaction = ft_signal_handler;
	sa_sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
}

void	ft_signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	int	pid;

	pid = getpid();
	(void)siginfo;
	(void)context;
	if (sig == SIGINT)
	{
		if (pid != 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			write(1, "\n", 1);
			rl_redisplay();
		}
	}
}
