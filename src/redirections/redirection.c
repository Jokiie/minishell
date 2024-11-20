/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/19 04:35:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect(t_minishell *ms, int return_value, int k, int *i)
{
	if (is_heredoc(ms->tokens[k]) && ms->token.protected[k] == 0)
	{
		if (return_value > 0)
			close(return_value);
		return_value = redirect_heredoc(ms, (*i)++);
	}
	else if (is_append(ms->tokens[k]) && ms->token.protected[k] == 0)
	{
		if (return_value > 0)
			close(return_value);
		return_value = append_output(ms->tokens[k + 1]);
	}
	else if (is_redirect_out(ms->tokens[k]) && ms->token.protected[k] == 0)
	{
		if (return_value > 0)
			close(return_value);
		return_value = redirect_output(ms->tokens[k + 1]);
	}
	else if (is_redirect_in(ms->tokens[k]) && ms->token.protected[k] == 0)
	{
		if (return_value > 0)
			close(return_value);
		return_value = redirect_input(ms->tokens[k + 1]);
	}
	return (return_value);
}

/* < : redirect input in the specified file */
int	redirect_input(char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
		return (FAIL);
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
		close(fdin);
		return (FAIL);
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
		return (FAIL);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
		close(fdout);
		return (FAIL);
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
		return (FAIL);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
		close(fdout);
		return (FAIL);
	}
	close(fdout);
	return (SUCCESS);
}

/* Redirect STDIN to the temporary heredoc file in the index i */
int	redirect_heredoc(t_minishell *ms, int i)
{
	int	fdin;

	fdin = open(ms->heredoc.fd_name[i], O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), ms->heredoc.fd_name[i]);
		return (FAIL);
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "ms: dup2 error: %s\n", strerror(errno));
		close(fdin);
		return (FAIL);
	}
	close(fdin);
	return (SUCCESS);
}
