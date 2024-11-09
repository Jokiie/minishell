/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/09 00:40:52 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	tokens_creator(t_minishell *ms, char *line)
{
	if (ft_open_quotes_checker(ms, line) != SUCCESS)
	{
		ft_fprintf(2, "ms: syntax error near unclosed quotes\n");
		return (SYNTAX_ERROR);
	}
	tokenizer(ms, line);
	transformer(ms);
	if (ms->tokens && check_syntax(ms->tokens) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SUCCESS);
}

void 	transformer(t_minishell *ms)
{
	char **tmp_pretokens;

	if (ms->pretokens)
	{
		ms->tokc = count_tokens(ms->pretokens);
		tmp_pretokens = ms->pretokens;
		ms->tokens = ft_envdup(ms->pretokens);
		ms->pretokens = characterizer(ms, ms->tokens);
		fill_protected_arr(ms, ms->pretokens);
		ms->tokens = trimmer(ms, ms->pretokens);
		free_tokens(tmp_pretokens);
	}
	if (!ms->pretokens || !ms->tokens)
	{
		free_tokens(ms->pretokens);
		ms->tokens = NULL;
	}
}
void	fill_protected_arr(t_minishell *ms, char **tokens)
{
	int k;
	int	i;

	i = 0;
	k = 0;
	while (tokens[k])
		k++;
	ms->token.protected = malloc(sizeof(int) * k);
	if (!ms->token.protected)
		return ;
	k = 0;
	while (tokens[k])
	{
		if (has_quotes(ms->tokens[k]))
			ms->token.protected[i] = 1;
		else
			ms->token.protected[i] = 0;
		k++;
		i++;
	}
	// k = 0;
	// for (int j = 0; j < i ; j ++)
	// {
	// 	ft_printf("protected: [%d][%d]\n", k, ms->token.protected[j]);
	// 	k++;
	// }
}