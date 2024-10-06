/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:25:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/05 23:43:41 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	if (fdin < 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		return ;
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error dup input\n");
		close(fdin);
		return ;
	}
	close(fdin);
}

void	redirect_output(char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		return ;
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error dup output\n");
		close(fdout);
		return ;
	}
	close(fdout);
}
