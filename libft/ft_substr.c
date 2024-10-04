/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:20:47 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/07 10:51:07 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	srclen;
	size_t	i;

	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	if (start >= srclen)
	{
		sub_s = (char *)ft_calloc(1, sizeof(char));
		return (sub_s);
	}
	if (len > srclen - start)
		len = srclen - start;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		sub_s[i] = s[start + i];
	sub_s[i] = '\0';
	return (sub_s);
}
