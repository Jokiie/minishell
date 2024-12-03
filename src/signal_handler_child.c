/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 02:26:12 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/03 02:49:27 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_child_signal(struct termios *stermios)
{
    tcsetattr(1, TCSAFLUSH, stermios);
    sigint_child();
    sigquit_child();

}

void    sigint_child(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}

void	sigquit_child(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGQUIT, &sa, NULL);
}
