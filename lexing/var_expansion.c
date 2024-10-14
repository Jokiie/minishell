/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:43:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/13 12:15:51 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*apply_var_expansion(char *token_dup, int i)
{
	char	*var;
	char	*before;
	char	*after;
	char	*new_token_dup;

	before = ft_substr(token_dup, 0, i);
	i++;
	var = var_extractor(token_dup, &i);
	after = ft_substr(token_dup, i, ft_strlen(token_dup) - i);
	new_token_dup = insert_variable_value(before, var, after);
	ft_free(token_dup);
	token_dup = new_token_dup;
	i = ft_strlen(before) + ft_strlen(getenv(var));
	ft_free(before);
	ft_free(var);
	ft_free(after);
	return (new_token_dup);
}
