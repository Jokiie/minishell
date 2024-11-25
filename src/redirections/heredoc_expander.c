/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:29:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 06:59:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(t_minishell *ms, char *line)
{
	if (!line)
		return (NULL);
	if (ms->heredoc.in_quotes == TRUE)
		return (ft_strdup(line));
	else
		return (heredoc_expander(ms, line));
}

char	*heredoc_expander(t_minishell *ms, char *line)
{
	char	*dup;
	char	*new_dup;
	int		i;

	i = 0;
	dup = ft_strdup(line);
	while (dup[i])
	{
		if (dup[i] == '$' && (ft_isalnum(dup[i + 1]) || dup[i + 1] == '_'))
		{
			new_dup = apply_var_expansion(ms, dup, i);
			dup = new_dup;
		}
		else if (dup[i] == '$' && dup[i + 1] == '?')
		{
			new_dup = apply_nbr_expansion(ms, dup, i);
			dup = new_dup;
		}
		else
			i++;
	}
	return (dup);
}
