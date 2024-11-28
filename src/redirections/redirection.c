/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/27 14:43:06 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* < : redirect input in the specified file */
int	redirect_input(char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		perror("ms");
		return (ERROR);
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		perror("ms");
		close(fdin);
		return (ERROR);
	}
	close(fdin);
	return (SUCCESS);
}

/* > : redirect output in the specified file */
int	redirect_output(char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fdout < 0)
	{
		perror("ms");
		return (ERROR);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		perror("ms");
		close(fdout);
		return (ERROR);
	}
	close(fdout);
	return (SUCCESS);
}

/* Redirect the output and append it in the specified file */
int	append_output(char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fdout < 0)
	{
		perror("ms");
		return (ERROR);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		perror("ms");
		close(fdout);
		return (ERROR);
	}
	close(fdout);
	return (SUCCESS);
}

int	redirect_heredocs(t_minishell *ms)
{
	int	return_value;

	return_value = 0;
	ms->heredoc.index = 0;
	if (!ms->heredoc.fd_name)
		return (ERROR);
	return_value = redirect_input(ms->heredoc.fd_name[ms->heredoc.index]);
	ms->heredoc.index++;
	return (return_value);
}
