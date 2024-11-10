/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/10 00:07:20 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	tokens_creator(t_minishell *ms, char *line)
{
	char **tmp_pretokens;

	if (ft_open_quotes_checker(ms, line) != SUCCESS)
	{
		ft_fprintf(2, "ms: syntax error near unclosed quotes\n");
		return (SYNTAX_ERROR);
	}
	tokenizer(ms, line);
	if (ms->pretokens)
	{
		fill_protected_arr(ms);
		ms->tokc = count_tokens(ms->pretokens);
		tmp_pretokens = ms->pretokens;
		ms->tokens = ft_envdup(ms->pretokens);
		ms->pretokens = characterizer(ms, ms->tokens);
		ms->tokens = trimmer(ms, ms->pretokens);
		free_tokens(tmp_pretokens);
	}
	if (!ms->pretokens || !ms->tokens)
	{
		free_tokens(ms->pretokens);
		ms->tokens = NULL;
	}
	if (ms->tokens && check_syntax(ms->tokens) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SUCCESS);
}

void	fill_protected_arr(t_minishell *ms)
{
	int k;
	int	i;

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
	// k = 0;
	// for (int j = 0; j < i ; j ++)
	// {
	// 	ft_printf("protected: [%d][%d]\n", k, ms->token.protected[j]);
	// 	k++;
	// }
}