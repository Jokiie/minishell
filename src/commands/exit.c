/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:36:52 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/02 05:22:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	detect_exit_call(t_minishell *ms, char **tokens, int is_child)
{
	int	return_value;

	return_value = 0;
	if (ft_strncmp(tokens[0], "exit\0", 5) == 0)
	{
		return_value = ft_exit(ms, tokens, is_child);
		return (return_value);
	}
	return (CMD_NOT_FOUND);
}

int	ft_exit(t_minishell *ms, char **tokens, int is_child)
{
	int	return_code;

	return_code = 0;
	if (((tokens[1] && tokens[2])) && (is_valid_arg(tokens[1])))
	{
		ft_fprintf(2, "ms: exit: too many arguments\n");
		return (ERROR);
	}
	if (tokens[1] && (!is_valid_arg(tokens[1]) || !is_valid_size(tokens[1])))
	{
		ft_fprintf(2, "ms: exit: %s: numeric argument required\n", tokens[1]);
		if (is_child == 1)
			return (SYNTAX_ERROR);
		else
			exit_minishell(ms, SYNTAX_ERROR);
	}
	else
	{
		if (tokens[1])
			return_code = ft_atol(tokens[1]);
		if (is_child == 1)
			return (return_code);
		exit_minishell(ms, return_code);
	}
	return (SUCCESS);
}

t_bool	is_valid_arg(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '-' || token[i] == '+')
		i++;
	while (token[i])
	{
		if (!ft_isdigit(token[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
