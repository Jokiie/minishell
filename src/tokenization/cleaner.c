/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:48:09 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/30 01:59:52 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cleaner(char **tokens, int *count, int *k, int *i)
{
	*k = 0;
	*i = 0;
	*count = count_tokens(tokens);
}

char	**cleaner(t_minishell *ms, char **tokens)
{
	char	**cleaned;
	int		count;
	int		k;
	int		i;

	init_cleaner(tokens, &count, &k, &i);
	cleaned = ft_calloc(count + 1, sizeof(char *));
	if (!cleaned)
		return (NULL);
	while (tokens[k] && k < count)
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

int	count_valid_tokens(char **tokens)
{
	int	k;
	int	count;

	k = 0;
	count = count_tokens(tokens);
	while (tokens[k])
	{
		if (tokens[k][0] != '\0')
		{
			count++;
		}
		k++;
	}
	return (count);
}
