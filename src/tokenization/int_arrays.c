/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:27:04 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 13:31:02 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_int_arrays(t_minishell *ms)
{
	init_quoted_array(ms, ms->pretokens);
	init_expanded_array(ms, ms->pretokens);
}

void	init_quoted_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	count;

	i = 0;
	k = 0;
	count = count_tokens(tokens);
	ms->token.quoted = ft_calloc(count + 1, sizeof(int));
	if (!ms->token.quoted)
		return ;
	k = 0;
	while (tokens[k] && k < count)
	{
		if (has_quotes(tokens[k])
            && open_quotes_checker(ms, tokens[k]) == SUCCESS)
			ms->token.quoted[i] = 1;
		else
			ms->token.quoted[i] = 0;
		k++;
		i++;
	}
}

void	init_expanded_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	size;

	size = count_tokens(tokens) * count_size(tokens);
	ms->token.expanded = ft_calloc((size * size), sizeof(int));
	ms->token.tmp_array = ft_calloc((size * size), sizeof(int));
	if (!ms->token.expanded || !ms->token.tmp_array)
		return ;
	i = 0;
	k = 0;
	while (tokens[k] && k < size)
	{
		if (is_expandable(ms, tokens[k], k) == TRUE
            && !is_heredoc_delim(ms, tokens, k))
			ms->token.expanded[i] = 1;
		else
			ms->token.expanded[i] = 0;
		k++;
		i++;
	}
	ms->token.expanded[i] = 0;
}

void	update_arrays(t_minishell *ms, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		ms->token.expanded[i] = ms->token.tmp_array[i];
		i++;
	}
	free(ms->token.tmp_array);
	free_int_array(&ms->token.quoted);
	init_quoted_array(ms, ms->pretokens);
}
