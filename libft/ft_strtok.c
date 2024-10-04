/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:01:53 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/02 22:19:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, char *delim)
{
	static char	*saved_str;
	char		*str_start;

	if (!delim)
		return (str);
	if (!str)
		str = saved_str;
	if (!str)
		return (NULL);
	while (*str && ft_is_delimiter(*str, delim))
		str++;
	if (*str == '\0')
		return (NULL);
	str_start = str;
	while (*str && !ft_is_delimiter(*str, delim))
		str++;
	if (*str)
	{
		*str = '\0';
		saved_str = str + 1; // pour le :
	}
	else
		saved_str = NULL; //pour commencer au '\0'
	return (str_start);
}
