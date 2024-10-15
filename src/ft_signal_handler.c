/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:21:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/15 14:39:21 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	to do:
	- handle ctrl-D -> quit the shell (if (!ms->prompt), in execms)
	- handle ctrl-C -> display a new prompt on a new line
						(send a SIGINT to the current executing process)
	- handle ctrl-\ -> subject said must do nothing and do like the true shell
						but the true shell send a SIGQUIT
*/
void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		//rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	ft_sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		;
}
