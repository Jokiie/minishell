/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:52:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/24 03:25:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**recreate_tokens(char **tokens, int **protected, int count, t_bool in_pipe)
{
	char	**new_tokens;
	int		*new_protected;
	int		i;
	int		j;
	
	(void)in_pipe;
    new_protected = ft_calloc((count + 1), sizeof(int));
    if (!new_protected)
	    return (NULL);
	new_tokens = ft_calloc((count + 1), sizeof(char *));
	if (!new_tokens)
	{
		free(new_protected);
		return (NULL);
	}
	j = 0;
	i = 0;
	while (tokens[i] && j < count)
	{
		while ((is_redirect(tokens[i]) || is_heredoc(tokens[i])) && (*protected)[i] == 0)
		{
			i += 2;
		}
		if (!tokens[i])
			break;
		new_tokens[j] = ft_strdup(tokens[i]);
		{
			if (!new_tokens[j])
			{
				free(new_protected);
				return (NULL);
			}
			new_protected[j] = (*protected)[i];
			j++;
			i++;
		}
	}
	new_tokens[j] = NULL;
	new_protected[j] = '\0';
	free(*protected);
	*protected = new_protected;
	return (new_tokens);
}

int	get_filtered_tokc(char **tokens, int **protected)
{
	int	count;
	int	i;

	i = 0;
	count = count_tokens(tokens);
	while (tokens[i])
	{
		if ((is_redirect(tokens[i]) || is_heredoc(tokens[i])) && (*protected)[i] == 0)
		{
			count = count - 2;
		}
		i++;
	}
	return (count);
}
