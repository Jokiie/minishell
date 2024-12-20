/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:32:54 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 23:00:24 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_minishell *ms)
{
	free_at_address(&ms->prompt_name);
	free_at_address(&ms->input);
	free_at_address(&ms->cwd);
	free_int_array(&ms->token.quoted);
	free_int_array(&ms->token.expanded);
	ms->token.db_buffer = NULL;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.quoted = NULL;
	ms->token.expanded = NULL;
	ms->token.is_meta = FALSE;
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.size = 1;
}

void	free_at_exit(t_minishell *ms)
{
	free_at_address(&ms->prompt_name);
	free_at_address(&ms->input);
	free_at_address(&ms->cwd);
	free_at_address(&ms->path);
	free_int_array(&ms->token.quoted);
	free_int_array(&ms->token.expanded);
	free_tokens_address(&ms->env);
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_at_address(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_int_array(int **arr)
{
	if (arr && *arr)
	{
		free(*arr);
		*arr = NULL;
	}
}
