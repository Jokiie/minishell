/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:07:44 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/06 22:08:16 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_heredoc(t_minishell *ms)
{
	int	k;
	int	count;

	count = 0;
	k = 0;
	while (ms->tokens[k])
	{
		if (is_heredoc(ms->tokens[k]))
			count++;
		k++;
	}
	return (count);
}
