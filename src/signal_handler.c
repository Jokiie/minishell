/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:21:50 by ccodere           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/18 11:45:58 by matislessar      ###   ########.fr       */
=======
/*   Updated: 2024/11/16 00:49:38 by ccodere          ###   ########.fr       */
>>>>>>> origin/dev
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
void	init_signals_interactive(void)
{
	struct sigaction	sa;

	handle_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &reset_prompt;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	reset_prompt(int sig)
{
	(void)sig;
	// rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	put_newline(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	init_signals_noninteractive(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &put_newline;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}