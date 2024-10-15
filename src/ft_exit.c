/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:31:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/15 14:58:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Free our variables, clear the history from readline, wait the child to
	finish and quit minishell
*/
void	exit_minishell(t_minishell *ms)
{
	int	status;

	ft_printf(BOLD GREEN "ms: Goodbye %s!\n" RESET BOLDRESET, ms->user);
	ft_free_vars2(ms);
	clear_history();
	while (waitpid(-1, &status, 0) > 0)
		;
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
