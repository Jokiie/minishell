/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:50:23 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 12:33:35 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	in_expandable_zone(t_minishell *ms, char *token, int i, int k)
{
	if (token[i] && token[i + 1]
		&& ms->token.state_array[k][ms->token.state_index] != 1
		&& ms->token.state_array[k][ms->token.state_index + 1] != 1)
	{
		if (token[i] == '$' && (ft_isalnum(token[i + 1])
				|| token[i + 1] == '_' || token[i + 1] == '?'))
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	is_variable_expansion(char *token, int i)
{
	if (token[i] == '$' && (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_return_code_expansion(char *token, int i)
{
	if (token[i] == '$' && token[i + 1] == '?')
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_heredoc_delim(t_minishell *ms, char **tokens, int k)
{
	if (k > 0 && (tokens[k] && is_heredoc(tokens[k - 1])
			&& ms->token.quoted[k - 1] == 0))
		return (TRUE);
	return (FALSE);
}
