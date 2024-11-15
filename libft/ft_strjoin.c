/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:07:50 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/14 15:42:11 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

static size_t	get_total_length(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	return (s1_len + s2_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*strs;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!str1 || !str2)
	{
		if (!str1 && !str2)
			return (NULL);
		else if (!str1)
			return (str2);
		else
			return (str1);
	}
	total_len = get_total_length(s1, s2);
	if (total_len == 0)
		return (ft_strdup(""));
	strs = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!strs)
		return (NULL);
	ft_strcpy(strs, s1);
	ft_strcat(strs, s2);
	return (strs);
}
