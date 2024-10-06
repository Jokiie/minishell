/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:31:13 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/05 23:38:14 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free the parameters and quit minishell */

void	ft_exit_minishell(t_minishell *ms)
{
	int	status;

	if (ms->prompt_name && ms->prompt && ms->cwd && ms->env)
	{
		free(ms->prompt_name);
		free(ms->prompt);
		free(ms->cwd);
		ft_free_tokens(ms->env);
		if (ms->tokens)
			ft_free_tokens(ms->tokens);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	exit(0);
}

void	ft_free_vars(t_minishell *ms)
{
	free(ms->prompt_name);
	free(ms->prompt);
	free(ms->cwd);
	ft_free_tokens(ms->env);
	if (ms->tokens)
		ft_free_tokens(ms->tokens);
}
