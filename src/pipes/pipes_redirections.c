/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:57:51 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/19 06:24:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_redirection_pipes(t_pipes *p, t_minishell *ms)
{
	static int	i = 0;
	int			k;
	int			return_value;
	int			count;

	return_value = 0;
	k = 0;
	//ft_fprintf(2, "Before redirection\n");
	//print_debug(p->p_args);
	while (p->p_args[k])
	{
		if ((is_heredoc(p->p_args[k]) || is_redirect(p->p_args[k]))
			&& p->arg_protected[k] == 0)
		{
			return_value = redirect_pipes(ms, p, return_value, k, &i);
			break ;
		}
		else
			k++;
		if (return_value == FAIL || return_value == FAIL)
			return (ERROR);
	}
	count = count_args_left(p);
	//ft_fprintf(2, "count = %d\n", count);
	recreate_pipes_args(p, count);
	//ft_fprintf(2, "After redirection\n");
	//print_debug(p->p_args);
	i = 0;
	return (return_value);
}

int	redirect_pipes(t_minishell *ms, t_pipes *p, int return_value, int k, int *i)
{
	if (is_heredoc(p->p_args[k]) && p->arg_protected[k] == 0)
	{

		return_value = redirect_heredoc(ms, (*i)++);
	}
	else if (is_append(p->p_args[k]) && p->arg_protected[k] == 0)
	{

		return_value = append_output(p->p_args[k + 1]);
	}
	else if (is_redirect_out(p->p_args[k]) && p->arg_protected[k] == 0)
	{

		return_value = redirect_output(p->p_args[k + 1]);
	}
	else if (is_redirect_in(p->p_args[k]) && p->arg_protected[k] == 0)
	{

		return_value = redirect_input(p->p_args[k + 1]);
	}
	return (return_value);
}

int	count_args_left(t_pipes *p)
{
	int	count;
	int	i;

	i = 0;
	count = count_tokens(p->p_args);
	while (p->p_args[i])
	{
		if ((is_redirect(p->p_args[i]) || is_heredoc(p->p_args[i])) && p->arg_protected[i] == 0)
		{
			count = count - 2;
		}
		i++;
	}
	if (count == 0)
		return (1);
	return (count);
}

void	recreate_pipes_args(t_pipes *p, int args_count)
{
	char	**new_args;
	int		i;
	int		j;
	
	new_args = (char **)malloc(sizeof(char *) * (args_count + 1));
	if (!new_args)
		return ;
	j = 0;
	i = 0;
	while (p->p_args[i])
	{
		while ((is_redirect(p->p_args[i]) || is_heredoc(p->p_args[i])) && p->arg_protected[i] == 0)
			i += 2;
		if (!p->p_args[i])
			break ;
		new_args[j] = ft_strdup(p->p_args[i]);
		j++;
		i++;
	}
	new_args[j] = NULL;
	free_tokens(p->p_args);
	p->p_args = new_args;
}
