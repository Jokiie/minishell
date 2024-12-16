/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 17:56:03 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Trimmer:
	Iter in each tokens and remove the quotes of tokens that do not result from
	expansion. This is the final step and the result is assigned to ms->tokens.
*/
char	**trimmer(t_minishell *ms, char **tokens)
{
	char	**trimmed;
	int		count;
	int		k;
	int		i;
	int		**tmp;

	k = 0;
	i = 0;
	count = count_tokens(tokens);
	trimmed = ft_calloc(count + 1, sizeof(char *));
	tmp = ft_calloc(count + 1, sizeof(int *));
	if (!trimmed)
		return (NULL);
	while (tokens[k])
	{
		tmp[k] = ft_calloc(ft_strlen(tokens[k]), sizeof(int));
		trimmed[i] = ft_toktrim(ms, tokens, tmp, k);
		if (trimmed[i])
			i++;
		k++;
	}
	trimmed[i] = NULL;
	tmp[i] = NULL;
	free_state_array(ms, count);
	ms->token.state_array = tmp;
	return (trimmed);
}

char	*ft_toktrim(t_minishell *ms, char **tokens, int **tmp, int k)
{
	char	*buffer;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(tokens[k]);
	buffer = ft_calloc((len + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (tokens[k][i])
	{
		if ((ft_is_dquote(tokens[k][i]) && ms->token.state_array[k][i] == 2)
			|| (ft_is_squote(tokens[k][i]) && ms->token.state_array[k][i] == 1))
			i++;
		else
		{
			buffer[j] = tokens[k][i];		
			tmp[k][j] = ms->token.state_array[k][i];
			j++;
			i++;
		}
	}
	buffer[j] = '\0';
	return (buffer);
}
