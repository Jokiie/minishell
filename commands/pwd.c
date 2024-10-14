/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/14 04:22:21 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/* Call the pwd command */
int	detect_pwd_call(char **tokens)
{
	if (ft_strnstr(tokens[0], "pwd", 3))
	{
		pwd(tokens);
		return (SUCCESS);
	}
	return (FAIL);
}

/* Display the current working directory */
void	pwd(char **tokens)
{
	char	*cwd;
	char	cwd_buffer[BUFFER_SIZE];

	if (tokens[1] != NULL)
	{
		ft_fprintf(2, "pwd: too many arguments\n");
		return ;
	}
	cwd = getcwd(cwd_buffer, MAX_PATH);
	if (!cwd)
	{
		ft_fprintf(2, "pwd: getcwd\n");
		return ;
	}
	else
		ft_printf("%s\n", cwd);
}
