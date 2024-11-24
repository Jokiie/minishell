
#include "../includes/minishell.h"

/*
	Free our variables, clear the history from readline, wait the child to
	finish and quit minishell with the return status of the last command.
*/
void	exit_minishell(t_minishell *ms, int return_code)
{
	int	child_ret;

	//ft_printf(BOLD GREEN "ms: Goodbye %s!\n" RESET BOLDRESET, ms->user);
	free_at_exit(ms);
	reset_heredoc(ms);
	clear_history();
	while (waitpid(-1, &child_ret, 0) > 0)
		;
	free(ms);
	exit(return_code);
}

void	exit_child(t_minishell *ms, int return_code, t_bool in_pipe)
{
	free_at_exit(ms);
	if (in_pipe)
	{
		free_tokens_address(&ms->p.p_args);
		free_int_array(&ms->p.arg_protected);
		close_pipes(ms);
	}
	exit(return_code);
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
int	wait_children(void)
{
	pid_t	wait_pid;
	int		status;
	int		last_status;

	wait_pid = 0;
	last_status = 0;
	while (wait_pid != -1 || errno != ECHILD)
	{
		wait_pid = waitpid(-1, &status, 0);
		last_status = status;
	}
	if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGPIPE)
		return (0);
	else if (WIFSIGNALED(last_status))
		status = 128 + WTERMSIG(last_status);
	else if (WIFEXITED(last_status) && !WIFSIGNALED(last_status))
		status = WEXITSTATUS(last_status);
	else
		status = last_status;
	return (status);
}
