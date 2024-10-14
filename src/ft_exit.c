/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:31:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/14 14:00:30 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Free our variables, clear the history from readline, wait the child to
	finish and quit minishell
*/
void	ft_exit_minishell(t_minishell *ms)
{
	int	status;

	ft_printf(BOLD GREEN "ms: Goodbye %s!\n" RESET BOLDRESET, ms->user);
	ft_free_vars2(ms);
	clear_history();
	while (waitpid(-1, &status, 0) > 0)
		;
	exit(0);
}
