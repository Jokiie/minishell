/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:27:04 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/11 05:33:10 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_int_arrays(t_minishell *ms)
{
	init_quoted_array(ms, ms->pretokens);
	init_expanded_array(ms, ms->pretokens);
}

void	init_quoted_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	count;

	i = 0;
	k = 0;
	count = count_tokens(tokens);
	ms->token.quoted = ft_calloc(count + 1, sizeof(int));
	if (!ms->token.quoted)
		return ;
	k = 0;
	while (tokens[k] && k < count)
	{
		if (has_quotes(tokens[k]) && open_quotes_checker(ms,
				tokens[k]) == SUCCESS)
			ms->token.quoted[i] = 1;
		else
			ms->token.quoted[i] = 0;
		k++;
		i++;
	}
}

void	init_expanded_array(t_minishell *ms, char **tokens)
{
	int	k;
	int	i;
	int	size;

	size = count_tokens(tokens);
	ms->token.expanded = ft_calloc((size + 1), sizeof(int));
	if (!ms->token.expanded)
		return ;
	i = 0;
	k = 0;
	while (tokens[k])
	{
		if (is_expandable(ms, tokens[k], k) == TRUE && !is_heredoc_delim(ms,
				tokens, k))
			ms->token.expanded[i] = 1;
		else
			ms->token.expanded[i] = 0;
		k++;
		i++;
	}
	ms->token.expanded[i] = 0;
}

int	transfer_cexpanded_data(t_minishell *ms, int **tmp, int i, t_counter *count)
{
	size_t	exp_len;

	if (!ms->expanded[count->k])
		return (-1);
	exp_len = ft_strlen(ms->expanded[count->k]);
	quotes_detector_size_t(ms, ms->expanded[count->k], count->g);
    if ((ft_isspace(ms->expanded[count->k][count->g]) && !ms->token.in_squotes) 
		|| (ft_isspace(ms->expanded[count->k][count->g] && !ms->token.in_dquotes)))
    {
	    count->g++;
	}
	if (count->g < exp_len)
	{
    	tmp[i][count->j] = ms->token.cexpanded[count->k][count->g];
    	count->g++;
	}
	if (count->g >= exp_len)
    {
        count->g = 0;
        count->k++;
		if (!ms->expanded[count->k])
			return (-1);
    }
	return (0);
}

void	init_counter(t_counter *count)
{
	count->i = 0;
	count->j = 0;
	count->k = 0;
	count->g = 0;
}
void	update_cexpanded(t_minishell *ms, int buffer_size)
{
	size_t		len;
	int			**tmp;
	t_counter	count;

	tmp = ft_calloc(buffer_size + 1, sizeof(int **));
	if (!tmp)
		return ;
	init_counter(&count);
    while (count.i < buffer_size && ms->expanded[count.k])
    {
        len = ft_strlen(ms->token.db_buffer[count.i]);
        tmp[count.i] = ft_calloc(len, sizeof(int));
        count.j = 0;
        while (count.j < len && ms->expanded[count.k])
        {
            if (transfer_cexpanded_data(ms, tmp, count.i, &count) == -1)
				break ;
            count.j++;
        }
        count.i++;
    }
    tmp[count.i] = NULL;
    free_cexpanded(ms);
    ms->token.cexpanded = tmp;
}

void	update_arrays(t_minishell *ms, int buffer_size)
{
	if (!ms->token.db_buffer)
		return ;
	update_cexpanded(ms, buffer_size);
	free_int_array(&ms->token.quoted);
	init_quoted_array(ms, ms->token.db_buffer);
}

