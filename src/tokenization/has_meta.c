/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:08:28 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 23:56:08 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	has_type(char **tokens, int **quoted, int **expanded,
		t_bool (*is_type)(char *))
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if ((*quoted)[i] == 0 && (*expanded)[i] == 0 && is_type(tokens[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_redirects(char **tokens, int **quoted, int **expanded)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if ((*quoted)[i] == 0 && (*expanded)[i] == 0 && (is_redirect(tokens[i])
				|| is_heredoc(tokens[i])))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_quotes(char *token)
{
	if (ft_strchr(token, '\'') != NULL || ft_strchr(token, '\"') != NULL)
		return (TRUE);
	return (FALSE);
}
