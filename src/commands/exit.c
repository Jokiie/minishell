/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:36:52 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/06 23:13:32 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_minishell *ms, char **tokens, int is_child)
{
	int	ret;

	ret = 0;
	if (((tokens[1] && tokens[2])) && (is_valid_arg(tokens[1])))
	{
		ft_fprintf(2, "ms: exit: too many arguments\n");
		return (ERROR);
	}
	if (tokens[1] && (!is_valid_arg(tokens[1]) || !is_valid_size(tokens[1])))
	{
		ft_fprintf(2, "ms: exit: %s: numeric argument required\n", tokens[1]);
		if (is_child == 1)
			return (CATCH_ALL);
		else
			exit_minishell(ms, CATCH_ALL);
	}
	else
	{
		ret = handle_valid_exit(ms, tokens, is_child);
		if (is_child && !tokens[1])
			ret = ms->ret;
	}
	return (ret);
}

int	handle_valid_exit(t_minishell *ms, char **tokens, int is_child)
{
	int	ret;

	ret = 0;
	if (tokens[1])
		ret = ft_atol(tokens[1]) % 256;
	if (!is_child)
		exit_minishell(ms, ret);
	return (ret);
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
