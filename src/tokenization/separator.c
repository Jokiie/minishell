/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:30:30 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 23:39:21 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**separator(t_minishell *ms, char **tokens)
{
	ms->pretokens = retokenize(ms, tokens);
	return (ms->pretokens);
}

char	**retokenize(t_minishell *ms, char **tokens)
{
	int	i;
	int	k;
	int	j;
	int	size;
	int	*new;
	
	size = count_tokens(tokens) * count_size(tokens);
	ms->pretokens = ft_calloc((size + 1), sizeof(char *));
	new = ft_calloc((size + 1), sizeof(int));
	if (!ms->pretokens)
		return (NULL);
	j = 0;
	k = 0;
	i = 0;
	while (tokens[j] && k < size)
	{
		if (!tokens[j][0])
		{
			if (ms->token.expanded[j] == 1)
			{
				ms->pretokens[k] = ft_strdup("");
				new[k] = 1;
				k++;
			}
			j++;
		}
		else
		{
			while (tokens[j][i])
			{
				while (ft_isspace(tokens[j][i]))
					i++;
				i = separe_token(ms, tokens[j], i, &k);
				while (ft_isspace(tokens[j][i]))
					i++;
				new[k - 1] = ms->token.expanded[j];
			}
			j++;
			i = 0;
		}
	}
	ms->pretokens[k] = NULL;
	for (i = 0; i < k; i++)
		ms->token.expanded[i] = new[i];
	free(new);
	return (ms->pretokens);
}

int	separe_token(t_minishell *ms, char *line, int i, int *k)
{
	ms->token.is_meta = FALSE;
	ms->token.start = i;
	while (line[i])
	{
		quotes_detector(ms, line, i);
		if (!ms->token.in_dquotes && !ms->token.in_squotes)
		{
			if (ft_isspace(line[i]) && !ms->token.in_dquotes
				&& !ms->token.in_squotes)
				break ;
			else if (ft_ismeta_chars(line[i]) && !ms->token.in_dquotes
				&& !ms->token.in_squotes)
			{
				ms->token.is_meta = TRUE;
				break ;
			}
		}
		i++;
	}
	ms->token.end = i;
	ms->token.size = (ms->token.end - ms->token.start);
	if (i > ms->token.start)
		ms->pretokens[(*k)++] = ft_substr(line, ms->token.start,
				ms->token.size);
	else if (ms->token.is_meta)
		ms->pretokens[(*k)++] = meta_chars_extractor(line, &i);
	return (i);
}
