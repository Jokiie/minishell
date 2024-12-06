/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_detector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:30:53 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 22:40:32 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes_detector(t_minishell *ms, char *line, int i)
{
	if (ft_is_dquote(line[i]) && !ms->token.in_squotes)
	{
		ms->token.in_dquotes = !ms->token.in_dquotes;
	}
	else if (ft_is_squote(line[i]) && !ms->token.in_dquotes)
	{
		ms->token.in_squotes = !ms->token.in_squotes;
	}
	return (i);
}

int	quotes_detector_tokens(t_minishell *ms, char *tokens, int k, int i)
{
	if (ft_is_dquote(tokens[i]) && !ms->token.in_squotes
		&& ms->token.expanded[k] == 0)
	{
		ms->token.in_dquotes = !ms->token.in_dquotes;
	}
	else if (ft_is_squote(tokens[i]) && !ms->token.in_dquotes
		&& ms->token.expanded[k] == 0)
	{
		ms->token.in_squotes = !ms->token.in_squotes;
	}
	return (i);
}

int	quotes_detector_tokens2(t_minishell *ms, char *tokens, int i)
{
	if (ft_is_dquote(tokens[i]) && !ms->token.in_squotes)
	{
		ms->token.in_dquotes = !ms->token.in_dquotes;
	}
	else if (ft_is_squote(tokens[i]) && !ms->token.in_dquotes)
	{
		ms->token.in_squotes = !ms->token.in_squotes;
	}
	return (i);
}

int	open_quotes_checker(t_minishell *ms, char *line)
{
	int	i;

	i = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	while (line[i])
	{
		quotes_detector(ms, line, i);
		i++;
	}
	if (ms->token.in_dquotes == TRUE || ms->token.in_squotes == TRUE)
	{
		ms->token.in_dquotes = FALSE;
		ms->token.in_squotes = FALSE;
		return (ERROR);
	}
	return (SUCCESS);
}
