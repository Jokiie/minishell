/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:37:24 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/22 15:51:11 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*apply_nbr_value(char *token_dup, int i, int nbr)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, i);
	i++;
	var = single_var_extractor(token_dup, &i);
	after = ft_substr(token_dup, i, ft_strlen(token_dup) - i);
	new_token_dup = insert_nbr_value(before, after, nbr);
	ft_free(token_dup);
	token_dup = new_token_dup;
	i = ft_strlen(before) + ft_strlen(getenv(var));
	ft_free(before);
	ft_free(var);
	ft_free(after);
	return (new_token_dup);
}

char	*single_var_extractor(char *token, int *i)
{
	char	*substr;
	int		start;

	start = *i;
	(*i)++;
	substr = ft_substr(token, start, *i - start);
	return (substr);
}

char	*insert_nbr_value(char *before, char *after, int nbr)
{
	char	*var_value;
	char	*half_token;
	char	*complete_token;

	var_value = ft_itoa(nbr);
	if (!var_value)
		var_value = "";
	half_token = ft_strjoin(before, var_value);
	complete_token = ft_strjoin(half_token, after);
	ft_free(half_token);
	ft_free(var_value);
	return (complete_token);
}
