/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:52:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 02:14:40 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remake_tokens(t_minishell *ms, char **tok, int **quoted, int **expanded)
{
	char	**tmp;
	int		count;

	count = get_filtered_tokc(tok, quoted, expanded);
	if (ms->in_pipe)
	{
		tmp = ms->p.p_args;
		ms->p.p_args = recreate_tokens(tok, quoted, expanded, count);
		if (!ms->p.p_args)
			ms->p.p_args = NULL;
		free_tokens(tmp);
	}
	else if (!ms->in_pipe)
	{
		tmp = ms->tokens;
		ms->tokens = recreate_tokens(tok, quoted, expanded, count);
		if (!ms->tokens)
			ms->tokens = NULL;
		free_tokens(tmp);
	}
}

char	**recreate_tokens(char **tok, int **quoted, int **expanded, int count)
{
	char	**new_tokens;
	int		i;
	int		j;

	new_tokens = ft_calloc((count + 1), sizeof(char *));
	if (!new_tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (tok[i] && j < count)
	{
		while ((is_redirect(tok[i]) || is_heredoc(tok[i])) && (*quoted)[i] == 0
			&& (*expanded)[i] == 0)
			i += 2;
		if (!tok[i])
			break ;
		new_tokens[j] = ft_strdup(tok[i]);
		(*quoted)[j] = (*quoted)[i];
		(*expanded)[j] = (*expanded)[i];
		j++;
		i++;
	}
	return (new_tokens);
}

int	get_filtered_tokc(char **tokens, int **quoted, int **expanded)
{
	int	count;
	int	i;

	i = 0;
	count = count_tokens(tokens);
	while (tokens[i])
	{
		if ((is_redirect(tokens[i]) || is_heredoc(tokens[i]))
			&& (*quoted)[i] == 0 && (*expanded)[i] == 0)
		{
			count = count - 2;
		}
		i++;
	}
	return (count);
}
