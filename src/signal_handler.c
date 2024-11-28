/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:35:57 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/27 22:50:02 by ccodere          ###   ########.fr       */
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

void	sync_signals(t_minishell *ms)
{
	ms->received_sig = g_sig_received;
	g_sig_received = 0;
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
	g_sig_received = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//write(1, "\n", 1);
	//rl_redisplay();
}

void	put_newline(int sig)
{
	(void)sig;
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");

}

void	init_signals_noninteractive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &put_newline;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

/*
	This function wait the children created in the fork.
	For each iteration of wait, until it gets an error(-1) and no code 10,
	it will wait the child to terminate and save the status in last status.
	At the end, we check the status to assign the appropriate return value
	to the final status :

	ECHILD = ECHILD : no child job (code 10) // stop the loop in we get this
	WIFSIGNALED = Child got kill by a signal
	WTERMSIG = if WIFSIGNALED we get the signum that killed the child
	WIFEXITED = Check if the child terminated normally
	WEXITSTATUS = If WIFEXITED we get the exit code of the child

	bash calculate the error return this way : 128 + signum
*/
int	wait_children(t_minishell *ms)
{
	pid_t	wait_pid;
	int		status;
	int		last_status;

	wait_pid = 0;
	last_status = 0;
	while (wait_pid != -1 || errno != ECHILD)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == ms->pid)
			last_status = status;
	}
	if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGPIPE)
		return (status);
	else if (WIFSIGNALED(last_status))
		status = 128 + WTERMSIG(last_status);
	else if (WIFEXITED(last_status) && !WIFSIGNALED(last_status))
		status = WEXITSTATUS(last_status);
	else
		status = last_status;
	return (status);
}
