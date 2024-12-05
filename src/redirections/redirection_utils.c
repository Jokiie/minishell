/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:52:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 01:35:19 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remake_tokens(t_minishell *ms, char **tokens, int **quoted, int **expanded,
		t_bool in_pipe)
{
	char	**tmp;
	int		count;

	count = get_filtered_tokc(tokens, quoted, expanded);
	if (in_pipe)
	{
		tmp = ms->p.p_args;
		ms->p.p_args = recreate_tokens(tokens, quoted, expanded, count, 0);
		if (!ms->p.p_args)
			ms->p.p_args = NULL;
		free_tokens(tmp);
	}
	else if (!in_pipe)
	{
		tmp = ms->tokens;
		ms->tokens = recreate_tokens(tokens, quoted, expanded, count, 0);
		if (!ms->tokens)
			ms->tokens = NULL;
		free_tokens(tmp);
	}
}

char	**recreate_tokens(char **tok, int **arr, int **arr2, int count, int i)
{
	char	**new_tokens;
	int		*new_quoted;
	int		*new_expanded;
	int		j;

	new_tokens = ft_calloc((count + 1), sizeof(char *));
	if (!new_tokens)
		return (NULL);
	new_quoted = ft_calloc((count + 1), sizeof(int));
	if (!new_quoted)
		return (NULL);
	new_expanded = ft_calloc((count + 1), sizeof(int));
	if (!new_expanded)
		return (NULL);
	j = 0;
	while (tok[i] && j < count)
	{
		while ((is_redirect(tok[i]) || is_heredoc(tok[i])) && (*arr)[i] == 0 && (*arr2)[i] == 0)
			i += 2;
		if (!tok[i])
			break ;
		new_tokens[j] = ft_strdup(tok[i]);
		new_quoted[j] = (*arr)[i];
		new_expanded[j] = (*arr2)[i];
		j++;
		i++;
	}
	free(*arr);
	*arr = new_quoted;
	free(*arr2);
	*arr2 = new_expanded;
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
