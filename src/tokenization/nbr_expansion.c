/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:37:24 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 12:27:09 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*can_apply_nbr_expansion(t_minishell *ms, char *token_dup, int *i,
		int k)
{
	char	*new_token_dup;

	new_token_dup = NULL;
	if (is_return_code_expansion(token_dup, *i) == TRUE
		&& (ms->token.state_array[k][ms->token.state_index] != 1
		&& ms->token.state_array[k][ms->token.state_index + 1] != 1
		&& token_dup[*i] && token_dup[*i + 1]))
		new_token_dup = apply_nbr_expansion(ms, token_dup, i, k);
	return (new_token_dup);
}

char	*apply_nbr_expansion(t_minishell *ms, char *token_dup, int *i, int k)
{
	char	*before;
	char	*after;
	char	*new_token_dup;
	char	*nbr;

	before = ft_substr(token_dup, 0, *i);
	ms->token.expansion_start = *i;
	(*i) += 2;
	after = ft_substr(token_dup, *i, ft_strlen(token_dup) - *i);
	nbr = ft_itoa(ms->ret);
	new_token_dup = insert_nbr_value(before, nbr, after);
	free_ptr(token_dup);
	token_dup = new_token_dup;
	*i = ft_strlen(before) + ft_strlen(nbr);
	fill_3_new_state_array(ms, ms->token.expansion_start, ft_strlen(nbr), k);
	free_ptr(before);
	free_ptr(nbr);
	free_ptr(after);
	ms->token.state_index += 2;
	return (new_token_dup);
}

char	*insert_nbr_value(char *before, char *nbr, char *after)
{
	char	*half_token;
	char	*complete_token;

	if (!nbr)
		nbr = "";
	half_token = ft_strjoin(before, nbr);
	complete_token = ft_strjoin(half_token, after);
	free_ptr(half_token);
	return (complete_token);
}
