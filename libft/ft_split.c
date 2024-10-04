/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:13:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/21 00:04:47 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wrdcnt(char const *s, char sep)
{
	size_t	count;
	int		inside_word;

	inside_word = 0;
	count = 0;
	if (!s)
		return ('\0');
	while (*s)
	{
		if (*s != sep)
		{
			if (!inside_word)
			{
				count++;
				inside_word = 1;
			}
		}
		else
			inside_word = 0;
		s++;
	}
	return (count);
}

static size_t	ft_wrdlen(const char *s, char sep)
{
	size_t	len;

	len = 0;
	while (*s && *s != sep)
	{
		len++;
		s++;
	}
	return (len);
}

static void	ft_free(char **result, size_t i)
{
	while (i > 0)
	{
		i--;
		free(result[i]);
		result[i] = NULL;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	len;
	size_t	i;

	result = (char **)ft_calloc(ft_wrdcnt(s, c) + 1, sizeof(char *));
	if (!s || !result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = ft_wrdlen(s, c);
			result[i] = ft_strndup(s, len);
			if (!result[i] && (ft_free(result, i), 1))
				return (NULL);
			i++;
			s += len;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
