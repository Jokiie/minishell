/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:29:35 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/18 23:59:44 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(t_minishell *ms, char *line)
{
	char	*tmp_line;

	if (!line)
		return (NULL);
	if (ms->heredoc.in_quotes == FALSE && ft_strchr(line, '$'))
	{
		tmp_line = expander(ms, line);
		if (tmp_line)
		{
			ft_free(line);
			line = tmp_line;
		}
		else
			ft_free(line);
	}
	return (line);
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
