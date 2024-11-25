/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:29:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/22 15:14:08 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(t_minishell *ms, char *line)
{
	if (!line)
		return (NULL);
	if (ms->heredoc.in_quotes == TRUE)
		return (ft_strdup(line));
	return (expander(ms, line));
}

char	*expander(t_minishell *ms, char *line)
{
	char	*line_dup;
	char	*new_line_dup;
	int		i;

	i = 0;
	line_dup = ft_strdup(line);
	while (line_dup[i])
	{
		if (line_dup[i] == '$' && (ft_isalnum(line_dup[i + 1]) || line_dup[i
				+ 1] == '_'))
		{
			new_line_dup = apply_var_expansion(line_dup, i);
			line_dup = new_line_dup;
		}
		else if (line_dup[i] == '$' && line_dup[i + 1] == '?')
		{
			new_line_dup = apply_nbr_expansion(ms, line_dup, i);
			line_dup = new_line_dup;
		}
		else
			i++;
	}
	return (line_dup);
}
