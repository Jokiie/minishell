/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:31:12 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/19 15:24:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	ssize;
	size_t	dsize;

	if (!src || !dst)
		return (0);
	srcsize = ft_strlen(src);
	dsize = dstsize - 1;
	ssize = srcsize;
	if ((srcsize + 1) < dstsize)
	{
		while (ssize-- && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	else if (dstsize != 0)
	{
		while (dsize-- && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (srcsize);
}
