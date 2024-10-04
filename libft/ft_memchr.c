/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:18:22 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/09 11:39:07 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Memchr is use to find the first occurance of a character in a block of 
// memory. Unlike strstr / strnstr, it can be use on other data and not only 
// strings. Memchr return the location of the character following by the
// remaining data. 
// Example
// int tab[4] = { 1, 2 ,3 ,4 };
// int *res = ft_memchr(tab, 3, sizeof(tab));
// printf("%d\n", *res); -> ouput: 3
void	*ft_memchr(const void *str, int c, unsigned int len)
{
	unsigned char	*s;
	unsigned char	*found;

	found = NULL;
	s = (unsigned char *)str;
	while ((s != NULL) && (len--))
	{
		if (*s != (unsigned char) c)
			s++;
		else
		{
			found = s;
			break ;
		}
	}
	return (found);
}
