/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/11 18:02:52 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	tokens_creator(t_minishell *ms, char *line)
{
	if (!line || is_only_spaces(line) == TRUE)
	{
		ms->tokens = NULL;
		return (0);
	}
	if (ft_open_quotes_checker(ms, line) != SUCCESS)
	{
		ft_fprintf(2, "ms: syntax error near unclosed quotes\n");
		return (SYNTAX_ERROR);
	}
	tokenizer(ms, line);
	ms->tokens = transformer(ms);
	if (ms->tokens && check_syntax(ms->tokens) == SYNTAX_ERROR)
	{
		free_tokens(ms->tokens);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

t_bool	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	**transformer(t_minishell *ms)
{
	char	**tmp_pretokens;
	char	**tmp_tokens;

	if (!ms->pretokens && !*ms->pretokens)
		return (NULL);
	fill_protected_arr(ms);
	ms->tokc = count_tokens(ms->pretokens);
	tmp_pretokens = ms->pretokens;
	ms->tokens = ft_envdup(ms->pretokens);
	tmp_tokens = ms->tokens;
	ms->pretokens = characterizer(ms, ms->tokens);
	if (!*ms->pretokens[0])
	{
		free_tokens(tmp_pretokens);
		free_tokens(tmp_tokens);
		ms->pretokens = NULL;
		return (NULL);
	}
	ms->tokens = trimmer(ms, ms->pretokens);
	free_tokens(tmp_pretokens);
	if (!*ms->tokens[0] && !ms->token.protected[0])
		return (NULL);
	return (ms->tokens);
}

void	fill_protected_arr(t_minishell *ms)
{
	int k;
	int i;

	i = 0;
	k = 0;
	while (ms->pretokens[k])
		k++;
	ms->token.protected = malloc(sizeof(int) * k);
	if (!ms->token.protected)
		return ;
	k = 0;
	while (ms->pretokens[k])
	{
		if (has_quotes(ms->pretokens[k]))
			ms->token.protected[i] = 1;
		else
			ms->token.protected[i] = 0;
		k++;
		i++;
	}
}