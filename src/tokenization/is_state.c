/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 05:31:46 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 11:54:14 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_quoted_state(t_minishell *ms, int *i, int k)
{
	if (ms->token.state_array[k][*i] == 1 || ms->token.state_array[k][*i] == 2
		|| ms->token.state_array[k][*i] == 4)
		return (TRUE);
	return (FALSE);
}

t_bool	is_squoted_state(t_minishell *ms, int *i, int k)
{
	if (ms->token.state_array[k][*i] == 1)
		return (TRUE);
	return (FALSE);
}

t_bool	is_expanded_state(t_minishell *ms, int *i, int k)
{
	if (ms->token.state_array[k][*i] == 3 || ms->token.state_array[k][*i] == 4)
		return (TRUE);
	return (FALSE);
}
