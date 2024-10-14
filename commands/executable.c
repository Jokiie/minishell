/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:14:31 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/13 22:25:46 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	detect_executable(t_minishell *ms, char **tokens, int k)
{
	if (ft_strnstr(tokens[k], "./", 2))
	{
		if (execve(tokens[k], tokens, ms->env) == -1)
			ft_fprintf(2, "ms: no such file or directory: %s\n", tokens[k]);
		return (SUCCESS);
	}
	return (FAIL);
}
