/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:04:56 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/04 13:01:32 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Iter in each token and search an unquoted '$' and replace the variable by
	its value in the environment. If the value is NULL, replace the $VAR with
	a empty str. If '$' is followed by another '$', we just write the dollars
	signs until a '$' sign is followed by a letter, number or '?'. In this case,
	we replace the variable by the value of the environment variable or the
	return value of the last command if it's a '?'.
*/
void	init_expanded_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	count;

	count = count_tokens(tokens);
	ms->token.expanded = ft_calloc(count + 1, sizeof(int));
	if (!ms->token.expanded)
		return ;
	i = 0;
	k = 0;
	while (tokens[k] && k < count)
	{
		if (tokens[k][0] == '$' && tokens[k][1] && var_is_squoted(ms, tokens[k]) != TRUE)
		{
			if (ft_isalpha(tokens[k][1]) || tokens[k][1] == '_')
				ms->token.expanded[i] = 1;
		}
		else
			ms->token.expanded[i] = 0;
		k++;
		i++;
	}
}

t_bool	var_is_squoted(t_minishell *ms, char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		quotes_detector(ms, tokens, i);
		if (tokens[i] == '$' && ms->token.in_squotes == TRUE
			&& ms->token.in_dquotes == FALSE)
		{
			ms->token.in_squotes = FALSE;
			return (TRUE);
		}
		i++;
	}
	ms->token.in_squotes = FALSE;
	ms->token.in_dquotes = FALSE;
	return (FALSE);
}

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
	while (tokens[k] && k < count)
	{
		if (k > 0 && (is_heredoc(tokens[k - 1]) && ms->token.quoted[k - 1] == 0) && tokens[k])
			expanded[i] = ft_strdup(tokens[k]);
		else
			expanded[i] = expand_token(ms, tokens[k], k, 0);
		if (expanded)
			i++;
		k++;
	}
	expanded[i] = NULL;
	return (expanded);
}

char	*expand_token(t_minishell *ms, char *token, int k, int i)
{
	char	*dup;
	char	*new_dup;

	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	dup = ft_strdup(token);
	while (dup[i])
	{
		quotes_detector_tokens(ms, dup, k, i);
		if (dup[i] == '$' && !ms->token.in_squotes
			&& (ft_isalnum(dup[i + 1]) || dup[i + 1] == '_'))
		{
			new_dup = apply_var_expansion(ms, dup, &i);
			dup = new_dup;
		}
		else if (dup[i] == '$' && !ms->token.in_squotes && dup[i + 1] == '?')
		{
			new_dup = apply_nbr_expansion(ms, dup, &i);
			dup = new_dup;
		}
		else
			i++;
	}
	return (dup);
}
