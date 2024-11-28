/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:32:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/26 01:54:44 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free_int_array(&ms->p.arg_quoted);
		close_pipes(ms);
	}
	exit(return_code);
}
