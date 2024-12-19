/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:17:12 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 15:23:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = dstlen;
	j = 0;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while (src[j] && i < dstsize -1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dstlen + srclen);
}
