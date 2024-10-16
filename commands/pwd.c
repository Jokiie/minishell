/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/16 02:06:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/* Call the pwd command */
int	detect_pwd_call(t_minishell *ms, char **tokens)
{
	if (ft_strnstr(tokens[0], "pwd", 3))
	{
		pwd(ms, tokens);
		return (SUCCESS);
	}
	return (FAIL);
}

/* Display the current working directory */
void	pwd(t_minishell *ms, char **tokens)
{

	if (tokens[1] != NULL)
	{
		ft_fprintf(2, "pwd: too many arguments\n");
		return ;
	}
	else
		ft_printf("%s\n", ms->cwd);
}
