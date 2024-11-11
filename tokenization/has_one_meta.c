/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_one_meta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:08:21 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/08 14:57:26 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_bool	has_redirect_in(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && is_redirect_in(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_redirect_out(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && is_redirect_out(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_append(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && is_append(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_heredoc(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && is_heredoc(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_pipe(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && is_pipe(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
