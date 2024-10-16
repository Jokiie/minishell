/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:31:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/15 23:03:07 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Free our variables, clear the history from readline, wait the child to
	finish and quit minishell
*/
void	exit_minishell(t_minishell *ms)
{
	int	child_ret;

	ft_free_vars2(ms);
	rl_clear_history();
	while (waitpid(-1, &child_ret, 0) > 0)
		;
	ft_printf(BOLD GREEN "ms: Goodbye %s!\n" RESET BOLDRESET, ms->user);
	free(ms);
	exit(0);
}
void	exit_child(t_minishell *ms)
{
	int	status;

	ft_free_vars2(ms);
	clear_history();
	while (waitpid(-1, &status, 0) > 0)
		;
	exit(0);
}
