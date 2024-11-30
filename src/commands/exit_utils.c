/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 04:06:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/30 05:04:08 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_valid_size(char *token)
{
	char		*long_max;
	char		*long_min_max;

	long_max = "9223372036854775807";
	long_min_max = "-9223372036854775808";
	if (ft_strlen(token) < ft_strlen(long_min_max) - 1)
		return (TRUE);
	if ((ft_isdigit(token[0]) && ft_strlen(token) > ft_strlen(long_max))
		|| (token[0] == '-' && ft_strlen(token) > ft_strlen(long_min_max)))
		return (FALSE);
	if (ft_isdigit(token[0]) || token[0] == '+')
	{
		if (iter_long_max(token) != TRUE)
			return (FALSE);
	}
	else if (token[0] == '-')
	{
		if (iter_long_min(token) != TRUE)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	iter_long_min(char *token)
{
	char	*long_min_max;
	int		i;

	long_min_max = "-9223372036854775808";
	i = 1;
	while (token[i + 1])
		i++;
	while (i > 1)
	{
		if (token[i] > long_min_max[i])
			return (FALSE);
		i--;
	}
	return (TRUE);
}

t_bool	iter_long_max(char *token)
{
	char	*long_max;
	int		i;
	int		j;
	
	long_max = "9223372036854775807";
	j = 0;
	i = 0;
	if (token[0] == '+')
		i++;
	while (token[i])
		i++;
	i--;
	while (long_max[j])
		j++;
	j--;
	while (j >= 0 && i >= 0)
	{
		if (token[i] > long_max[j])
			return (FALSE);
		i--;
		j--;
	}
	return (TRUE);
}
