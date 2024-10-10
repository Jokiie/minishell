/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/10 16:48:11 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "commands.h"

/*
Display the current working directory
*/
void	pwd(char **tokens)
{
	char	cwd[BUFFER_SIZE];

	if (tokens[1] != NULL)
	{
		ft_fprintf(2, "pwd: too many arguments\n");
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		ft_fprintf(2, "getcwd() error");
		return ;
	}
}
