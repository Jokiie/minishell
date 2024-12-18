/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:55:05 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/18 15:48:12 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parser(t_minishell *ms, char **tokens)
{
	int	k;
	int	count;
	int	len;

	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	ms->token.state_array = ft_calloc(count + 1, sizeof(int *));
	k = 0;
	while (tokens[k] && k < count)
	{
		len = ft_strlen(tokens[k]);
		init_token_state_array(ms, len, k);
		fill_state_array(ms, tokens[k], k);
		k++;
	}
	ms->token.state_array[k] = NULL;
	return (tokens);
}

void	fill_state_array(t_minishell *ms, char *token, int k)
{
	int	i;

	i = 0;
	while (token[i])
	{
		quotes_detector(ms, token, i);
		if (ft_is_dquote(token[i]))
			i = parse_dquotes(ms, token, i, k);
		else if (ft_is_squote(token[i]))
			i = parse_squotes(ms, token, i, k);
		else
			add_to_state_array(ms, 0, k);
		i++;
	}
}

int	parse_squotes(t_minishell *ms, char *token, int i, int k)
{
	if (!token)
		return (i);
	if (ft_is_squote(token[i]) && !ms->token.in_dquotes)
	{
		add_to_state_array(ms, SQUOTE, k);
		while (token[++i] && !ft_is_squote(token[i]))
			add_to_state_array(ms, SQUOTE, k);
		// i = i;
		add_to_state_array(ms, SQUOTE, k);
		quotes_detector(ms, token, i);
	}
	return (i);
}

int	parse_dquotes(t_minishell *ms, char *token, int i, int k)
{
	if (!token)
		return (i);
	if (ft_is_dquote(token[i]) && !ms->token.in_squotes)
	{
		add_to_state_array(ms, DQUOTE, k);
		while (token[++i] && !ft_is_dquote(token[i]))
			add_to_state_array(ms, DQUOTE, k);
		add_to_state_array(ms, DQUOTE, k);
		quotes_detector(ms, token, i);
	}
	return (i);
}
