/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 12:23:03 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Trimmer:
	Iter in each tokens and remove the quotes that do not result from expansion.
	If ms->token.state_array stored a state of 1 or 2 and this character is a
	single quote or a double quote and we will not add them in the new buffer.
*/
char	**trimmer(t_minishell *ms, char **tokens)
{
	t_counter	c;
	char		**trimmed;
	int			count;
	int			**tmp;

	init_counter(&c);
	count = count_tokens(tokens);
	trimmed = ft_calloc(count + 1, sizeof(char *));
	tmp = ft_calloc(count + 1, sizeof(int *));
	if (!trimmed)
		return (NULL);
	while (tokens[c.k])
	{
		tmp[c.k] = ft_calloc(ft_strlen(tokens[c.k]), sizeof(int));
		trimmed[c.i] = ft_toktrim(ms, tokens, tmp, c.k);
		if (trimmed[c.i])
			c.i++;
		c.k++;
	}
	trimmed[c.i] = NULL;
	tmp[c.i] = NULL;
	free_state_array(ms, count);
	ms->token.state_array = tmp;
	return (trimmed);
}

t_bool	is_a_quote(t_minishell *ms, char **tokens, int i, int k)
{
	if ((ft_is_dquote(tokens[k][i]) && !ms->token.in_squotes
		&& ms->token.state_array[k][i] == 2) || (ft_is_squote(tokens[k][i])
		&& !ms->token.in_dquotes && ms->token.state_array[k][i] == 1))
		return (TRUE);
	return (FALSE);
}

char	*ft_toktrim(t_minishell *ms, char **tokens, int **tmp, int k)
{
	t_counter	c;
	char		*buffer;
	int			len;

	init_counter(&c);
	len = ft_strlen(tokens[k]);
	buffer = ft_calloc((len + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (tokens[k][c.i])
	{
		quotes_detector(ms, tokens[k], c.i);
		if (is_a_quote(ms, tokens, c.i, k))
			c.i++;
		else
		{
			buffer[c.j] = tokens[k][c.i];
			tmp[k][c.j] = ms->token.state_array[k][c.i];
			c.i++;
			c.j++;
		}
	}
	buffer[c.j] = '\0';
	return (buffer);
}
