/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:43:51 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/09 11:43:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Memcmp compares byte string s1 against byte string s2. Both strings are 
// assumed to be 'n' bytes long. The function return the difference of order 
// of the characters in the ascii table.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == s2)
			return (0);
		else if (s1 == NULL)
			return (-1);
		else
			return (1);
	}
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
