/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:52:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/19 06:25:19 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tokens_left(t_minishell *ms)
{
	int	count;
	int	i;

	i = 0;
	count = ms->tokc;
	while (ms->tokens[i])
	{
		if ((is_redirect(ms->tokens[i]) || is_heredoc(ms->tokens[i])) && ms->token.protected[i] == 0)
		{
			count = count - 2;
		}
		i++;
	}
	if (count == 0)
		return (1);
	return (count);
}

void	recreate_tokens(t_minishell *ms, int tokens_count)
{
	char	**new_tokens;
	int		i;
	int		j;

	new_tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
	if (!new_tokens)
		return ;
	j = 0;
	i = 0;
	while (ms->tokens[i])
	{
		while ((is_redirect(ms->tokens[i]) || is_heredoc(ms->tokens[i])) && ms->token.protected[i] == 0)
			i += 2;
		if (!ms->tokens[i])
			break;
		new_tokens[j] = ft_strdup(ms->tokens[i]);
		j++;
		i++;
	}
  	if (j == 0 && has_redirect(ms, ms->tokens))
        new_tokens[j++] = ft_strdup("cat");
	new_tokens[j] = NULL;
	free_tokens(ms->tokens);
	ms->tokens = new_tokens;
	ms->tokc = count_tokens(ms->tokens);
}
