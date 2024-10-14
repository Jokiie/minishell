/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:30:24 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/14 14:14:20 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_vars(t_minishell *ms)
{
	ft_free(ms->prompt_name);
	ft_free(ms->cwd);
	ft_free_tokens(ms->env);
	ft_free_tokens(ms->tokens);
}

void	ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	ft_free_vars2(t_minishell *ms)
{
	ft_free2(&ms->prompt_name);
	ft_free2(&ms->prompt);
	ft_free2(&ms->cwd);
	ft_free_tokens(ms->env);
	ft_free_tokens(ms->tokens);
}

void	ft_free2(char **str)
{
	if (str && *str)
	{
		free(*str);
		str = NULL;
	}
}

void	ft_free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			ft_free(tokens[i]);
			i++;
		}
		free(tokens);
		tokens = NULL;
	}
}
