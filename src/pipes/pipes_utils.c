/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:18:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 02:53:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_pipes_protected_array(t_minishell *ms, int i)
{
	int	j;
	int	count;

	j = 0;
	count = count_tokens(ms->p.p_args);
	ms->p.arg_protected = malloc(sizeof(int) * (count + 1));
	if (!ms->p.arg_protected)
		return ;
	while (ms->p.p_args[j])
	{
		if (ms->token.protected[i] == 1)
			ms->p.arg_protected[j] = 1;
		else
			ms->p.arg_protected[j] = 0;
		j++;
		i++;
	}
}

char	**extract_args(char **tokens, int start, int end)
{
	int		i;
	int		size;
	char	**args;

	size = end - start;
	if (size <= 0)
		return (NULL);
	args = ft_calloc(size + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < size)
	{
		args[i] = tokens[start + i];
		i++;
	}
	args[size] = NULL;
	return (args);
}

void	handle_last_cmd(t_minishell *ms, int *i)
{
	if (ms->tokens[*i + 1] == NULL)
	{
		(*i)++;
		ms->p.last_cmd = TRUE;
	}
}
