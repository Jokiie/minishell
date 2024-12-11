/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_nbr_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:03:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/10 01:05:45 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*apply_nbr_expansion_hd(t_minishell *ms, char *token_dup, int *i)
{
	char	*new_token_dup;

	new_token_dup = NULL;
	if ((token_dup[*i] == '$' && token_dup[*i + 1] == '?')
		&& !ms->token.in_squotes)
		new_token_dup = apply_nbr_value_hd(token_dup, i, ms->ret);
	return (new_token_dup);
}

char	*apply_nbr_value_hd(char *token_dup, int *i, int nbr)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, *i);
	(*i)++;
	var = single_var_extractor_hd(token_dup, i);
	after = ft_substr(token_dup, *i, ft_strlen(token_dup) - *i);
	new_token_dup = insert_nbr_value_hd(before, after, nbr);
	free_ptr(token_dup);
	token_dup = new_token_dup;
	*i = ft_strlen(before) + ft_strlen(var);
	free_ptr(before);
	free_ptr(var);
	free_ptr(after);
	return (new_token_dup);
}

char	*single_var_extractor_hd(char *token, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	(*i)++;
	substr = ft_substr(token, start, *i - start);
	return (substr);
}

char	*insert_nbr_value_hd(char *before, char *after, int nbr)
{
	char	*var_value;
	char	*half_token;
	char	*complete_token;

	var_value = ft_itoa(nbr);
	if (!var_value)
		var_value = "";
	half_token = ft_strjoin(before, var_value);
	complete_token = ft_strjoin(half_token, after);
	free_ptr(half_token);
	free_ptr(var_value);
	return (complete_token);
}
