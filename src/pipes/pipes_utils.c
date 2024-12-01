/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:18:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/01 01:49:35 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_pipes_quoted_arr(t_minishell *ms, int i)
{
	int	j;
	int	count;

	j = 0;
	count = count_tokens(ms->p.p_args);
	ms->p.arg_quoted = ft_calloc(count + 1, sizeof(int));
	if (!ms->p.arg_quoted)
		return ;
	while (ms->p.p_args[j])
	{
		if (ms->token.quoted[i] == 1)
			ms->p.arg_quoted[j] = 1;
		else
			ms->p.arg_quoted[j] = 0;
		j++;
		i++;
	}
}

char	**extract_args(t_minishell *ms, char **tokens, int start, int end)
{
	int		i;
	int		j;
	int		size;
	char	**args;

	size = end - start;
	if (size <= 0)
		return (NULL);
	args = ft_calloc(size + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (tokens[start + i][0] != '\0'
			|| (tokens[start + i][0] == '\0' && ms->token.quoted[start + i] == 1))
		{
			args[j] = tokens[start + i];
			j++;
		}
		i++;
	}
	args[j] = NULL;
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
