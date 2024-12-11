/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:48:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/09 16:08:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Cleaner:
	Called only if no unquoted and no expanded pipes is found.
	It will iter in each tokens and remove the unquoted empty tokens
	resulted from the previous step (usually from empty variables).
*/
static void	init_cleaner(int *k, int *i)
{
	*k = 0;
	*i = 0;
}

char	**cleaner(t_minishell *ms, char **tokens)
{
	char	**cleaned;
	int		count;
	int		k;
	int		i;

	init_cleaner(&k, &i);
	count = count_valid_tokens(ms, tokens);
	cleaned = ft_calloc(count + 1, sizeof(char *));
	if (!cleaned)
		return (NULL);
	while (tokens[k])
	{
		if (tokens[k][0] || (!tokens[k][0] && ms->token.quoted[k] == 1))
		{
			cleaned[i] = ft_strdup(tokens[k]);
			if (cleaned[i])
			{
				ms->token.quoted[i] = ms->token.quoted[k];
				i++;
			}
		}
		k++;
	}
	cleaned[i] = NULL;
	return (cleaned);
}

int	count_valid_tokens(t_minishell *ms, char **tokens)
{
	int	k;
	int	count;

	k = 0;
	count = count_tokens(tokens);
	while (tokens[k])
	{
		if (tokens[k][0] == '\0' && ms->token.quoted[k] == 0)
		{
			count--;
		}
		k++;
	}
	return (count);
}
