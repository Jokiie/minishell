/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:47:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 15:10:03 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_dquote(int c)
{
	return (c == '\"');
}

int	ft_is_squote(int c)
{
	return (c == '\'');
}

int	ft_is_quotes(int c)
{
	return (ft_is_dquote(c) || ft_is_squote(c));
}

int	ft_ismeta_chars(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_bool	is_quoted_char(t_minishell *ms, int *i, int k)
{
	if (ms->token.state_array[k][*i] == 1
		|| ms->token.state_array[k][*i] == 2
		|| ms->token.state_array[k][*i] == 4)
			return (TRUE);
	return (FALSE);
}

t_bool	is_squoted_char(t_minishell *ms, int *i, int k)
{
	if (ms->token.state_array[k][*i] == 1)
			return (TRUE);
	return (FALSE);
}
t_bool	is_expanded_char(t_minishell *ms, int *i, int k)
{
	if (ms->token.state_array[k][*i] == 3
		|| ms->token.state_array[k][*i] == 4)
			return (TRUE);
	return (FALSE);
}
