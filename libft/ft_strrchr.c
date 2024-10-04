/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:01:59 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/24 14:15:36 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Find the last occurance of c in str
char	*ft_strrchr(const char *str, int c)
{
	const char	*last_occ;

	last_occ = NULL;
	if (str != NULL)
	{
		while (1)
		{
			if (*str == (char)c)
				last_occ = str;
			if (*str == '\0')
				return ((char *)last_occ);
			str++;
		}
	}
	return (NULL);
}
