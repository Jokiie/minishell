/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:37:47 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/09 12:03:17 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Memset writes 'len' bytes of value 'c' to the memory area 'byte'.
// Exemple
// char str[5] = "Celia";
// ft_memset(str, 'a', ft_strlen(str));
// printf("%s\n", str); -> output: aaaaa
void	*ft_memset(void *byte, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = byte;
	if (byte == NULL)
		return (NULL);
	while (len--)
		*ptr++ = (unsigned char)c;
	return (byte);
}
