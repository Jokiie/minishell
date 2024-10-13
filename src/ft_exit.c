/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:31:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/13 03:49:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Free the parameters and quit minishell
	to do:
	- handle ctrl-D -> quit the shell (in the execms, in minishell.c :
						if (ms->prompt == NULL)
							ft_exit_minishell(ms); // this do a segfault for now
	- handle ctrl-C -> display a new prompt on a new line
						(send a SIGINT to the current executing process)
	- handle ctrl-\ -> subject said must do nothing but do like the true shell
						but the true shell send a SIGQUIT
*/
void	ft_exit_minishell(t_minishell *ms)
{
	int	status;

	ft_free(ms->prompt_name);
	ft_free(ms->prompt);
	ft_free(ms->cwd);
	ft_free_tokens(ms->env);
	ft_free_tokens(ms->tokens);
	while (waitpid(-1, &status, 0) > 0)
		;
	exit(0);
}

void	ft_free_vars(t_minishell *ms)
{
	ft_free(ms->prompt_name);
	ft_free(ms->prompt);
	ft_free(ms->cwd);
	ft_free_tokens(ms->env);
	ft_free_tokens(ms->tokens);
}
