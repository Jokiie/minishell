/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:11 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/18 16:01:30 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_child_process(t_minishell *ms, t_pipes *p)
{
	int	return_value;

	return_value = 0;
	if (p->cmd_num > 0)
	{
		if (dup2(p->pipes[p->cmd_num - 1][0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (p->cmd_num < p->num_pipes)
	{
		if (dup2(p->pipes[p->cmd_num][1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(EXIT_FAILURE);
		}
	}
	close_pipes(p);
	ms->cmd_path = get_path(p->p_args[0]);
	return_value = call_commands_pipes(ms, p);
	free(ms->cmd_path);
	exit(return_value);
}

int	create_and_manage_process(t_minishell *ms, t_pipes *p, pid_t *pid)
{
	int	return_value;

	return_value = 0;
	*pid = fork();
	if (*pid == 0)
		handle_child_process(ms, p);
	else
	{
		return_value = wait_children();
		if (p->cmd_num < p->num_pipes)
			close(p->pipes[p->cmd_num][1]);
		if (p->cmd_num > 0)
			close(p->pipes[p->cmd_num - 1][0]);
	}
	return (return_value);
}

void	init_pipes(t_pipes *p)
{
	p->p_args = NULL;
	p->num_pipes = 0;
	p->cmd_num = 0;
	p->pipes = NULL;
}

void	tokenize_input1(t_minishell *ms)
{
	int		i;
	char	*token;

	ms->tokens = malloc(sizeof(char *) * 1024);
	i = 0;
	token = ft_strtok(ms->input, " \t\n|");
	while (token)
	{
		ms->tokens[i++] = strdup(token);
		token = ft_strtok(NULL, " \t\n|");
	}
	ms->tokens[i] = NULL;
}

void	recreate_pipes_args(t_pipes *p, int i)
{
	char	**new_args;
	int		k;

	new_args = (char **)malloc(sizeof(char *) * (i + 1));
	k = 0;
	while (k < i)
	{
		if (!is_redirect(p->p_args[k]))
			new_args[k] = p->p_args[k];
		k++;
	}
	new_args[k] = NULL;
	p->p_args = new_args;
}