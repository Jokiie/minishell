/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:31:12 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/07 10:57:43 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	ssize;
	size_t	dsize;

	if (!src || !dst)
		return ('\0');
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
