/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:38:39 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/07 10:17:17 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	chosen_c;

	chosen_c = c;
	if (str == NULL)
		return (NULL);
	while (*str != chosen_c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return ((char *)str);
}
