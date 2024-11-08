/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/08 14:52:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_bool	has_redirect(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && (is_redirect_in(tokens[i]) || is_redirect_out(tokens[i])
			|| is_append(tokens[i])))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_meta(t_minishell *ms, char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && (is_redirect(tokens[i]) || is_pipe(tokens[i])
			|| is_heredoc(tokens[i])))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_quotes(char *token)
{
	if (ft_strnstr(token, "\'", 1) != NULL || ft_strnstr(token, "\"", 1) != NULL)
		return (TRUE);
	return (FALSE);
}