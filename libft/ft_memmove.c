/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:47:21 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/09 11:55:14 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Memmove copies 'len' bytes from memory area 'src' to 'dst'. The two area
// can overlap. Memmove returns the original value of 'dst';
// Example
// char str[11] = "Hello World";
// char *res =ft_memmove(str, str + 6, 6);
// printf("%s\n", res); -> output: World World
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_ptr;
	const char	*src_ptr;
	char		*last_dst;
	const char	*last_src;

	dst_ptr = dst;
	src_ptr = src;
	last_dst = dst_ptr + (len - 1);
	last_src = src_ptr + (len - 1);
	if (!dst || !src)
		return (NULL);
	if (len == 0 || dst_ptr == src_ptr)
		return (dst);
	if (dst_ptr < src_ptr)
		while (len--)
			*dst_ptr++ = *src_ptr++;
	else
		while (len--)
			*last_dst-- = *last_src--;
	return (dst);
}
