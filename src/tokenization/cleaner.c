/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:48:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 11:29:16 by ccodere          ###   ########.fr       */
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
static void	init_cleaner(char ***cleaned, int count, int *k, int *i)
{
	*k = 0;
	*i = 0;
	*cleaned = ft_calloc(count + 1, sizeof(char *));
}

char	**cleaner(t_minishell *ms, char **tokens)
{
	char	**cleaned;
	int		count;
	int		k;
	int		i;

	count = count_valid_tokens(ms, tokens);
	init_cleaner(&cleaned, count, &k, &i);
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
				ms->token.expanded[i] = ms->token.expanded[k];
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
