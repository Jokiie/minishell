/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:11 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/24 03:10:46 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokens_creator(t_minishell *ms, char *line)
{
	if (!line || contains_only_spaces(line) == TRUE)
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
	if (!ms->pretokens)
	{
		ms->pretokens = NULL;
		ms->tokens = NULL;
		return (SUCCESS);
	}
	ms->tokens = transformer(ms);
	if (ms->tokens && check_syntax(ms->tokens) == SYNTAX_ERROR)
	{
		free_tokens(ms->tokens);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

char	**transformer(t_minishell *ms)
{
	char **tmp;
	char **final_tokens;
	
	ms->characterized = characterizer(ms, ms->pretokens);

	free_tokens(ms->pretokens);
	
	if (!ms->characterized)
		return (NULL);

	tmp = cleaner(ms->characterized);
	free_tokens(ms->characterized);
	
	ms->pretokens = tmp;
	if (!ms->pretokens)
		return (NULL);
		
	fill_protected_arr(ms, ms->pretokens);
	final_tokens = trimmer(ms, ms->pretokens);
	free_tokens(ms->pretokens);
	
	if (!final_tokens || !*final_tokens)
	{
		free_tokens(final_tokens);
		return (NULL);
	}
	ms->tokc = count_tokens(final_tokens);
	return (final_tokens);
}

void	fill_protected_arr(t_minishell *ms, char **tokens)
{
	int k;
	int i;
	int count;

	i = 0;
	k = 0;
	if (!tokens)
		return ;
	count = count_tokens(tokens);
	ms->token.protected = ft_calloc(count + 1, sizeof(int));
	if (!ms->token.protected)
		return ;
	k = 0;
	while (tokens[k] && k < count)
	{
		if (has_quotes(tokens[k]))
		{
			ms->token.protected[i] = 1;
		}
		else
		{
			ms->token.protected[i] = 0;
		}
		k++;
		i++;
	}
}
