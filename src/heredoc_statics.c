/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_statics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:02:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/06 22:09:44 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_heredoc_statics(void)
{
	update_heredoc_index(TRUE);
	update_heredoc_number(TRUE);
	update_heredoc_count(TRUE);
}

int	update_heredoc_index(t_bool reset)
{
	static int	count = -1;

	if (reset == TRUE)
	{
		count = -1;
		return (count);
	}
	return (++count);
}

int	update_heredoc_number(t_bool reset)
{
	static int	count = -1;

	if (reset == TRUE)
	{
		count = -1;
		return (count);
	}
	return (++count);
}

int	update_heredoc_count(t_bool reset)
{
	static int	count = -1;

	if (reset == TRUE)
	{
		count = -1;
		return (count);
	}
	return (++count);
}
