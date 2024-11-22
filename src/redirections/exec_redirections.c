/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:08:33 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/22 12:52:02 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Execute the adequate function for each redirection. A new list of tokens is
	created	without the redirections characters, allowing the command to be
	executed. Before this, the command couldn't execute because it attempted to
	interpret '<<', '>>', '<', and '>' as if it were a command or an argument
	to a command.
*/
int	exec_redirections(t_minishell *ms, char **tokens, int **protected,
		t_bool in_pipe)
{
	int	return_value;
	int	count;
	int	k;
	char	**tmp;

	ms->in_pipe = in_pipe;
	return_value = 0;
	//ft_fprintf(2, "Before redirection\n");
	//print_debug(tokens);
	//print_protected_array(tokens, protected);
	//ft_fprintf(2, "Heredocs name\n");
	//print_debug(ms->heredoc.fd_name);
	count = get_filtered_tokc(tokens, protected);
	//ft_fprintf(2, "count = %d\n", count);
	k = 0;
	while (tokens[k])
	{
		if (is_heredoc(tokens[k]) && (*protected)[k] == 0)
		{
			return_value = redirect_heredocs(ms);
			if (return_value != SUCCESS)
				return (return_value);
			k += 2;
		}
		else if (is_redirect(tokens[k]) && (*protected)[k] == 0)
		{
			return_value = redirect(tokens[k], tokens[k + 1]);
			if (return_value != SUCCESS)
				return (return_value);
			k += 2;
		}
		else
			k++;
	}
	if (in_pipe)
	{
		tmp = ms->p.p_args;
		ms->p.p_args = recreate_tokens(tokens, protected, count, in_pipe);
		free(tmp);
		//ft_fprintf(2, "After redirection\n");
		//print_debug(ms->p.p_args);
		//print_protected_array(ms->p.p_args, protected);
	}
	else if (!in_pipe)
	{
		ms->tokens = recreate_tokens(tokens, protected, count, in_pipe);
		//ft_fprintf(2, "After redirection\n");
		//print_debug(ms->tokens);
		//print_protected_array(ms->tokens, protected);
	}
	return (return_value);
}

int	redirect(char *tokens, char *file)
{
	int	return_value;

	return_value = 0;
	if (is_append(tokens))
	{
		return_value = append_output(file);
	}
	else if (is_redirect_out(tokens))
	{
		return_value = redirect_output(file);
	}
	else if (is_redirect_in(tokens))
	{
		return_value = redirect_input(file);
	}
	return (return_value);
}

int	redirect_heredocs(t_minishell *ms)
{
	int	return_value;

	return_value = 0;
	ms->heredoc.index = 0;
	if (!ms->heredoc.fd_name)
		return (ERROR);
	return_value = redirect_heredoc(ms->heredoc.fd_name[ms->heredoc.index]);
	ms->heredoc.index++;
	return (return_value);
}
