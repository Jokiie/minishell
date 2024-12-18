/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:33:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/18 15:59:43 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Print all the tokens in the STDIN followed by a new line.
*/
void	print_tokens(char **tokens)
{
	int	k;

	k = 0;
	if (!tokens || !*tokens)
		return ;
	while (tokens[k])
	{
		ft_printf("%s\n", tokens[k]);
		k++;
	}
}

/*
	Dup the environment string tab
	to do: need to check if we can use it to remove a variable
	with unset and re-add it with export.
*/
char	**ft_envdup(char **envp)
{
	char	**env_dup;
	int		i;
	int		j;
	int		size;

	if (!envp && !*envp)
		return (NULL);
	size = count_tokens(envp);
	env_dup = ft_calloc(sizeof(char *), (size + 1));
	if (!env_dup)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i] && j < size)
		env_dup[j++] = ft_strdup(envp[i++]);
	env_dup[j] = NULL;
	return (env_dup);
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
		return (0);
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	else if (WIFEXITED(last_status) && !WIFSIGNALED(last_status))
		return (WEXITSTATUS(last_status));
	return (last_status);
}
void	welcome(t_minishell *ms)
{
	char	*read;
	char	*user;

	read = NULL;
	user = get_user_color(ms);
	ft_printf(GREEN"\nWELCOME : %s\n", user);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	read = readline(read);
	free(read);
	free(user);
}
