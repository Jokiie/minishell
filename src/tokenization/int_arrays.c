/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:27:04 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 12:11:28 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Initialize and fill the int arrays that save the quoted and expanded state
	for each tokens, used for checking if a meta character is really a meta.
	A meta character that result from an expansion or is quoted is not
	considered meta by bash, so we did the same.
*/
void	init_int_arrays(t_minishell *ms, char **tokens)
{
	init_quoted_array(ms, tokens);
	init_expanded_array(ms, tokens);
}

void	init_quoted_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	size;

	size = count_tokens(tokens);
	ms->token.quoted = ft_calloc(size * 5, sizeof(int));
	if (!ms->token.quoted)
		return ;
	i = 0;
	k = 0;
	while (tokens[k] && k < size)
	{
		if (tokens[k])
		{
			if (has_quotes(tokens[k]) && open_quotes_checker(ms,
					tokens[k]) == SUCCESS)
				ms->token.quoted[i] = 1;
			else
				ms->token.quoted[i] = 0;
			k++;
			i++;
		}
		else
			break ;
	}
}

void	init_expanded_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	size;

	size = count_tokens(tokens);
	ms->token.expanded = ft_calloc(size * 5, sizeof(int));
	if (!ms->token.expanded)
		return ;
	i = 0;
	k = 0;
	while (tokens[k] && k < size)
	{
		if (tokens[k])
		{
			if (is_expandable(ms, tokens[k], k) == TRUE && !is_heredoc_delim(ms,
					tokens, k))
				ms->token.expanded[i] = 1;
			else
				ms->token.expanded[i] = 0;
			k++;
			i++;
		}
		else
			break ;
	}
}
