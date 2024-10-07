/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/06 01:50:16 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection_check(t_minishell *ms)
{
	int	k;

	k = 0;
	while (ms->tokens[k])
	{
		if (ft_strnstr(ms->tokens[k], ">", 1))
		{
			ms->redirection_needed = TRUE;
			return (k);
		}
		k++;
	}
	return (-1);
}

int		ft_exec_redirection(t_minishell *ms)
{
	int k;

	k = ft_redirection_check(ms);
	if (k > 0)
	{
		if (ft_strnstr(ms->tokens[k], ">", 1) && ms->redirection_needed)
		{
			redirect_output(ms, ms->tokens[k + 1]);
			ms->redirection_needed = FALSE;
			return (1);
		}
		else if (ft_strnstr(ms->tokens[k], "<", 1) && ms->redirection_needed)
		{
			redirect_input(ms, ms->tokens[k + 1]);
			ms->redirection_needed = FALSE;
			return (1);
		}
		return (-1);
	}
	else
		return (-1);
}
// <
void	redirect_input(t_minishell *ms, char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		return ;
	}
	if (dup2(fdin, ms->std_in) == -1)
	{
		ft_fprintf(2, "minishell: Error dup input\n");
		close(fdin);
		return ;
	}
	close(fdin);
}

// >
void	redirect_output(t_minishell *ms, char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		return ;
	}
	if (dup2(fdout, ms->std_out) == -1)
	{
		ft_fprintf(2, "minishell: Error dup output\n");
		close(fdout);
		return ;
	}
	close(fdout);
}
