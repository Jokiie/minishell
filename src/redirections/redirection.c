/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/22 12:37:03 by ccodere          ###   ########.fr       */
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
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
		return (ERROR);
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
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
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
		return (ERROR);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
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
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
		return (ERROR);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
		close(fdout);
		return (ERROR);
	}
	close(fdout);
	return (SUCCESS);
}

/* Redirect STDIN to the temporary heredoc file in the index i */
int	redirect_heredoc(char *file)
{
	int		fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "ms: heredoc: %s: %s\n", strerror(errno), file);
		return (ERROR);
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
		close(fdin);
		return (ERROR);
	}
	close(fdin);
	return (SUCCESS);
}
