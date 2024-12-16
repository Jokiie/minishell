/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:55:05 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/16 17:31:59 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **parser(t_minishell *ms, char **tokens)
{
	int k;
	int count;
	int len;

	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	ms->token.state_array = ft_calloc(count + 1 , sizeof(int *));
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

void fill_state_array(t_minishell *ms, char *token, int k)
{
	int i;

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


int parse_squotes(t_minishell *ms, char *token, int i, int k)
{
	if (!token)
		return (i);
	if (ft_is_squote(token[i]) && !ms->token.in_dquotes)
	{
		add_to_state_array(ms, SQUOTE, k);
		while (token[++i] && !ft_is_squote(token[i]))
			add_to_state_array(ms, SQUOTE, k);
		i = i;
		add_to_state_array(ms, SQUOTE, k);
		quotes_detector(ms, token, i);
	}
	return (i);
}

int parse_dquotes(t_minishell *ms, char *token, int i, int k)
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

int	get_expanded_state(t_minishell *ms, char **tokens, int k)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(tokens[k]);
	while (tokens[k][i] && i < len)
	{
		if (ms->token.state_array[k][i] >= 3)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int get_quoted_state(t_minishell *ms, char **tokens, int k)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(tokens[k]);
	while (tokens[k][i] && i < len)
	{
		if (ms->token.state_array[k][i] == 2
			|| ms->token.state_array[k][i] == 4
			|| ms->token.state_array[k][i] == 1
			|| has_quotes(tokens[k]) == TRUE)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_counter(t_counter *count)
{
	count->i = 0;
	count->j = 0;
	count->k = 0;
	count->g = 0;
}
int parse_quotes(t_minishell *ms, char *token, int **tmp, t_counter *count)
{
	if (!token)
		return (count->i);
	if (ft_is_squote(token[count->i]) && !ms->token.in_dquotes)
	{
		tmp[count->k][count->i] = SQUOTE;
		while (token[++count->i] && !ft_is_squote(token[count->i]))
			tmp[count->k][count->i] = SQUOTE;
		count->i = count->i;
		tmp[count->k][count->i] = SQUOTE;
		quotes_detector(ms, token, count->i);
	}
	else if (ft_is_dquote(token[count->i]) && !ms->token.in_squotes)
	{
		tmp[count->k][count->i] = DQUOTE;
		while (token[++count->i] && !ft_is_dquote(token[count->i]))
			tmp[count->k][count->i] = DQUOTE;
		count->i = count->i;
		tmp[count->k][count->i] = DQUOTE;
		quotes_detector(ms, token, count->i);
	}
	return (count->i);
}

int	update_state_array(t_minishell *ms, char **tokens)
{
	int	**tmp;
	int	count;
	int len;
	t_counter c;

	if (!tokens)
		return (-1);
	init_counter(&c);
	count = count_tokens(tokens);
	tmp = ft_calloc(count + 1, sizeof(int *));
	while (tokens[c.k] && c.k < count)
	{
		len = ft_strlen(tokens[c.k]);
		tmp[c.k] = ft_calloc(len, sizeof(int));
		c.i = 0;
		while(tokens[c.k][c.i] && c.i < len)
		{
			quotes_detector(ms, tokens[c.k], c.i);
			if (ft_is_quotes(tokens[c.k][c.i])
				&& ms->token.state_array[c.k][c.i] != 4)
				c.i = parse_quotes(ms, tokens[c.k], tmp, &c);
			else
			{
				tmp[c.k][c.i] = ms->token.state_array[c.k][c.i];
			}
			c.i++;
		}
		c.k++;
	}
	tmp[c.k] = NULL;
	free_state_array(ms, count);
	ms->token.state_array = tmp;
	return (0);
}
