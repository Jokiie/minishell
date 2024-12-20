/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:48:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 23:53:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Cleaner:
	Called only if no quoted and expanded pipes is found. It will iter in
	each tokens and remove the unquoted empty tokens resulted from the previous
	steps, usually from empty variables because we must keep the empty quoted
	strings. If we keep the empty strings, we will have empty pipes and get
	a syntax error.
*/
static void	init_cleaner(int *k, int *i)
{
	*k = 0;
	*i = 0;
}

void	cleaner(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;

	init_cleaner(&k, &i);
	while (tokens[k])
	{
		if (tokens[k][0] || (!tokens[k][0] && (ms->token.quoted[k] == 1)))
		{
			tokens[i] = tokens[k];
			ms->token.quoted[i] = ms->token.quoted[k];
			ms->token.expanded[i] = ms->token.expanded[k];
			i++;
		}
		else
			free(tokens[k]);
		k++;
	}
	tokens[i] = NULL;
}

int	count_valid_tokens(t_minishell *ms, char **tokens)
{
	int	k;
	int	count;

	k = 0;
	count = count_tokens(tokens);
	while (tokens[k] && k < count)
	{
		if (tokens[k][0] == '\0' && ms->token.quoted[k] == 0)
		{
			count--;
		}
		k++;
	}
	return (count);
}
