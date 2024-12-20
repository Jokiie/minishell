/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 03:59:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 22:57:43 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Init a dynamic char **buffer(dbuffer) with a capacity of initial_capacity
		+ 1.
	This is use for retokenizer, since we dont know the final tokens count
	after variables expansion. We update our 2 int arrays in the same time
	so we know which meta charactere are quoted /expanded so we don't
	evaluate them as meta. State_array is free at the end of the transformation
	but not the expanded and quoted array, because the two int arrays are used
	in pipes and redirections analyzing.
*/
char	**init_dbuffer(t_minishell *ms, size_t initial_capacity)
{
	ms->token.db_buffer = ft_calloc(initial_capacity + 1, sizeof(char *));
	if (!ms->token.db_buffer)
		return (NULL);
	ms->token.db_size = 0;
	ms->token.db_capacity = initial_capacity + 1;
	return (ms->token.db_buffer);
}

int	update_expanded(t_minishell *ms, int new_capacity)
{
	int	*new_expanded;

	new_expanded = ft_calloc(new_capacity, sizeof(int));
	if (!new_expanded)
		return (-1);
	ft_memcpy(new_expanded, ms->token.expanded, ms->token.db_capacity
		* sizeof(int));
	free_int_array(&ms->token.expanded);
	ms->token.expanded = new_expanded;
	return (0);
}

int	update_quoted(t_minishell *ms, int new_capacity)
{
	int	*new_quoted;

	new_quoted = ft_calloc(new_capacity, sizeof(int));
	if (!new_quoted)
		return (-1);
	ft_memcpy(new_quoted, ms->token.quoted, ms->token.db_capacity
		* sizeof(int));
	free_int_array(&ms->token.quoted);
	ms->token.quoted = new_quoted;
	return (0);
}

/*
	Append a char
		* to the ms->token.db_buffer and update the ms->token.expanded array.
*/
int	append_to_dbuffer_char(t_minishell *ms, char *data)
{
	size_t	new_capacity;
	char	**new_data;

	if (data && (ms->token.db_size >= ms->token.db_capacity - 1))
	{
		new_capacity = ms->token.db_capacity * 5;
		new_data = ft_realloc(ms->token.db_buffer, ms->token.db_capacity
				* sizeof(char *), new_capacity * sizeof(char *));
		if (!new_data)
			return (-1);
		ms->token.db_buffer = new_data;
		if (update_expanded(ms, new_capacity) < 0 || update_quoted(ms,
				new_capacity) < 0)
			return (-1);
		ms->token.db_capacity = new_capacity;
	}
	ms->token.db_buffer[ms->token.db_size] = data;
	ms->token.expanded[ms->token.db_size] = ms->token.expansion_state;
	ms->token.quoted[ms->token.db_size] = ms->token.quoted_state;
	ms->token.db_size++;
	return (0);
}
