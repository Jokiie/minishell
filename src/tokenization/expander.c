/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/10 04:31:23 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Expander:
	Iter in each token and search a '$' character. If not a heredoc delimiter
	and is not single quoted, replace the variable by its value in the
	environment. If the value is NULL, replace the $VAR with a empty str. If '$'
	is followed by another '$', we just write the dollars signs until a '$' sign
	is followed by a letter, number or '?'. If this is the case, we replace the
	variable by the value of the environment variable or the return value of
	the last command if it's a '?'.
*/

char	**expander(t_minishell *ms, char **tokens)
{
	char	**expanded;
	int		count;
	int		k;
	int		i;

	k = 0;
	i = 0;
	count = count_tokens(tokens);
	expanded = ft_calloc(count + 1, sizeof(char *));
	if (!expanded)
		return (NULL);
	ms->token.cexpanded = ft_calloc(count + 1, sizeof(int *));
	while (tokens[k] && k < count)
	{
		init_cexpanded_int(ms, ft_strlen(tokens[k]), i);
		if (!is_expandable(ms, tokens[k], k) || is_heredoc_delim(ms, tokens, k))
		{
			expanded[i] = ft_strdup(tokens[k]);
			fill_0_cexpanded(ms, 0, ft_strlen(expanded[i]), i);
		}
		else
			expanded[i] = expand_token(ms, tokens[k], i);
		if (expanded)
			i++;
		k++;
	}
	ms->token.cexpanded[i] = NULL;
	expanded[i] = NULL;
	return (expanded);
}

char	*expand_token(t_minishell *ms, char *token, int cexpindex)
{
	char	*dup;
	char	*new_dup;
	int		i;
	
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	if (!token)
		return (NULL);
	dup = ft_strdup(token);
	i = 0;
	while (dup[i])
	{
		quotes_detector(ms, dup, i);
		if (ms->token.in_squotes == FALSE && (dup[i] == '$' && (ft_isalnum(dup[i + 1]) || dup[i + 1] == '_' || dup[i + 1] == '?')))
		{
			if (dup[i] == '$' && (ft_isalnum(dup[i + 1]) || dup[i + 1] == '_'))
			{
				new_dup = apply_var_expansion(ms, dup, &i, cexpindex);
				dup = new_dup;
			}
			else if (dup[i] == '$' && dup[i + 1] == '?')
			{
				new_dup = apply_nbr_expansion(ms, dup, &i, cexpindex);
				dup = new_dup;
			}
		}
		else
		{
			append_to_cexpanded(ms, 0, cexpindex);
			i++;
		}
	}
	return (dup);
}

t_bool	is_expandable(t_minishell *ms, char *token, int k)
{
	int		i;
	t_bool	expandable;

	expandable = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.in_dquotes = FALSE;
	i = 0;
	while (token[i])
	{
		quotes_detector2(ms, token, k, i);
		if (token[i] == '$' && ms->token.in_squotes == FALSE
			&& (ft_isalpha(token[i + 1]) || token[i + 1] == '_' || token[i
				+ 1] == '?'))
		{
			expandable = TRUE;
		}
		i++;
	}
	ms->token.in_squotes = FALSE;
	ms->token.in_dquotes = FALSE;
	if (expandable == TRUE)
		return (TRUE);
	return (FALSE);
}

t_bool	is_exp_start(char *dup, int i)
{
	if (dup[i] == '$' && (ft_isalnum(dup[i + 1]) || dup[i + 1] == '_' || dup[i
			+ 1] == '?'))
		return (TRUE);
	return (FALSE);
}

t_bool	is_heredoc_delim(t_minishell *ms, char **tokens, int k)
{
	if (k > 0 && (is_heredoc(tokens[k - 1]) && ms->token.quoted[k - 1] == 0)
		&& tokens[k])
		return (TRUE);
	return (FALSE);
}
