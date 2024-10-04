/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:44:09 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/09 11:47:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Memcpy copy 'n'  bytes from memory area 'src' to 'dst'.
// Example
// char *src = "Hello";
// char *dst[6];
// ft_memcpy(dst, src, 6);
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_byte;
	const unsigned char	*src_byte;

	dst_byte = (unsigned char *)dst;
	src_byte = (unsigned char *)src;
	if (dst == NULL || src == NULL)
		return (dst);
	if (n == 0 || dst_byte == src_byte)
		return (dst);
	while (n--)
		*dst_byte++ = *src_byte++;
	return (dst);
}
