/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:29:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 02:10:18 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(t_minishell *ms, char *line, char *delim)
{
	if (!line)
		return (NULL);
	if (ms->heredoc.in_quotes == TRUE)
		return (ft_strdup(line));
	else
		return (heredoc_expander(ms, line, delim));
}

char	*heredoc_expander(t_minishell *ms, char *line, char *delim)
{
	char	*dup;
	char	*new_dup;
	int		i;

	i = 0;
	if (ft_strncmp(delim, line, ft_strlen(line)) == 0 && is_same_size(line,
			delim) == TRUE)
		return (ft_strdup(line));
	dup = ft_strdup(line);
	while (dup[i])
	{
		if (dup[i] == '$' && (ft_isalnum(dup[i + 1]) || dup[i + 1] == '_'))
		{
			new_dup = apply_var_expansion(ms, dup, &i);
			dup = new_dup;
		}
		else if (dup[i] == '$' && dup[i + 1] == '?')
		{
			new_dup = apply_nbr_expansion(ms, dup, &i);
			dup = new_dup;
		}
		else
			i++;
	}
	return (dup);
}

t_bool	is_same_size(char *str1, char *str2)
{
	if (ft_strlen(str1) == ft_strlen(str2))
		return (TRUE);
	return (FALSE);
}
