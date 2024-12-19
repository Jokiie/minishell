/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 03:19:33 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 12:28:34 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(t_minishell *ms)
{
	if (error_pipes(ms) != SUCCESS || errors_redirect(ms) != SUCCESS)
		return (SYNTAX_ERROR);
	return (SUCCESS);
}

int	error_pipes(t_minishell *ms)
{
	int	k;

	k = 0;
	while (ms->tokens[k])
	{
		if (is_pipe(ms->tokens[k]) && !ms->token.quoted[k])
		{
			if (k == 0 || ms->tokens[k + 1] == NULL
				|| (is_pipe(ms->tokens[k + 1]) && !ms->token.quoted[k + 1]))
			{
				ft_fprintf(2, "ms: syntax error near unexpected token `|'\n");
				return (SYNTAX_ERROR);
			}
		}
		k++;
	}
	return (SUCCESS);
}

int	errors_redirect(t_minishell *ms)
{
	int	k;

	k = 0;
	while (ms->tokens[k])
	{
		if ((is_redirect(ms->tokens[k]) || is_heredoc(ms->tokens[k]))
			&& !ms->token.quoted[k])
		{
			if (ms->tokens[k + 1] == NULL)
			{
				ft_fprintf(2,
					"ms: syntax error near unexpected token `newline'\n");
				return (SYNTAX_ERROR);
			}
			else if (is_meta(ms->tokens[k + 1]) && !ms->token.quoted[k + 1])
			{
				ft_fprintf(2, "ms: syntax error near unexpected token `%s'\n",
					ms->tokens[k + 1]);
				return (SYNTAX_ERROR);
			}
		}
		k++;
	}
	return (SUCCESS);
}
