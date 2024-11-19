/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:18:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/19 05:08:56 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_arg_protected_array(t_pipes *p)
{
	int i = 0;

	while (p->p_args[i])
	{
		ft_fprintf(2, "arg_protected[%d] = %d\n", i, p->arg_protected[i]);
		i++;
	}
}

int	count_pipes(t_minishell *ms, char **str)
{
	int	i;
	int	num_pipes;

	i = 0;
	num_pipes = 0;
	while (str[i])
	{
		if (ms->token.protected[i] == 0 && is_pipe(str[i]))
		{
			num_pipes++;
		}
		i++;
	}
	return (num_pipes);
}

void	fill_pipes_protected_array(t_minishell *ms, t_pipes *p, int i)
{
	int j;
	int	count;
	
	j = 0;
	count = count_tokens(p->p_args);
	p->arg_protected = malloc(sizeof(int) * (count + 1));
	if (!p->arg_protected)
		return;
	while (p->p_args[j])
	{
		if (ms->token.protected[i] == 1)
			p->arg_protected[j] = 1;
        else
            p->arg_protected[j] = 0;
		j++;
		i++;
	}
}

t_bool  pipes_has_redirect(t_pipes *p)
{
    int i;

    i = 0;
    while (p->p_args[i])
    {
        if ((is_redirect(p->p_args[i]) || is_heredoc(p->p_args[i])) && p->arg_protected[i] == 0)
            return (TRUE);
        i++;
    }
    return (FALSE);
}