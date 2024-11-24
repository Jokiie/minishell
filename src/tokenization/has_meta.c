/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/23 04:46:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	has_redirect(t_minishell *ms, char **tokens)
{
	int	i;

	i = 0;
	if (!tokens || !*tokens)
		return (FALSE);
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && is_redirect(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_type(char **tokens, int **protected, t_bool (*is_type)(char *))
{
	int	i;

	i = 0;
	if (!tokens || !*tokens)
		return (FALSE);
	while (tokens[i])
	{
		if ((*protected)[i] == 0 && is_type(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_meta(t_minishell *ms, char **tokens)
{
	int i;

	i = 0;
	if (!tokens || !*tokens)
		return (FALSE);
	while (tokens[i])
	{
		if (ms->token.protected[i] == 0 && (is_redirect(tokens[i]) || is_pipe(tokens[i])))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_quotes(char *token)
{
	if (!token)
		return (FALSE);
	if (ft_strchr(token, '\'') != NULL || ft_strchr(token, '\"') != NULL)
		return (TRUE);
	return (FALSE);
}