/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:11:15 by ccodere           #+#    #+#             */
/*   Updated: 2023/12/05 16:59:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *nd, size_t len)
{
	char			*h;
	char			*n;
	unsigned int	i;
	unsigned int	j;

	h = (char *)hs;
	n = (char *)nd;
	if (!hs || !nd)
		return (NULL);
	if (!n[0])
		return (h);
	if (len == 0)
		return (NULL);
	i = 0;
	while (i < len && h[i])
	{
		j = 0;
		while ((i + j) < len && h[i + j] == n[j]
			&& n[j])
			j++;
		if (n[j] == '\0')
			return (h + i);
		i++;
	}
	return (NULL);
}
