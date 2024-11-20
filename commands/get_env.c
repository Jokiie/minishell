/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:22:49 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/20 15:11:58 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	*get_env(char **env, char *var_name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
