/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 04:47:35 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	tokens_creator(t_minishell *ms, char *line)
{
	char	**tmp_pretokens;
	
	if (ft_open_quotes_checker(ms, line) != SUCCESS)
	{
		ft_fprintf(2, "ms: syntax error : unclosed quotes\n");
		return (SYNTAX_ERROR);
	}
	tokenizer(ms, line);
	if (ms->pretokens)
	{
		ms->tokc = ft_count_tokens(ms->pretokens);
		tmp_pretokens = ms->pretokens;
		ms->tokens = ft_envdup(ms->pretokens);
		ms->pretokens = characterizer(ms, ms->tokens);
		ms->tokens = trimmer(ms, ms->pretokens);
		ft_free_tokens(tmp_pretokens);
	}
	if (!ms->pretokens || !ms->tokens)
	{
		ft_free_tokens(ms->pretokens);
		ms->tokens = NULL;
	}
	if (ms->tokens && check_syntax(ms->tokens) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SUCCESS);
}
