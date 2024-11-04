/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_detector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:30:53 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 02:59:24 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	ft_quotes_detector(t_minishell *ms, char *line, int i)
{
	if (ft_is_dquote(line[i]) && !ms->token.in_squotes)
		ms->token.in_dquotes = !ms->token.in_dquotes;
	else if (ft_is_squote(line[i]) && !ms->token.in_dquotes)
		ms->token.in_squotes = !ms->token.in_squotes;
	return (i);
}

int	ft_open_quotes_checker(t_minishell *ms, char *line)
{
	int	i;

	i = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	while (line[i])
	{
		ft_quotes_detector(ms, line, i);
		i++;
	}
	if (ms->token.in_dquotes == TRUE || ms->token.in_squotes == TRUE)
		return (ERROR);
	return (SUCCESS);
}
