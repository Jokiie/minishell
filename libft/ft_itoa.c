/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:01:06 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/04 00:10:25 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Example
// int num = -424242;
// printf("%s\n", ft_itoa(num));
static int	ft_numlen(int n)
{
	int	len;

	len = !n;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_signed(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		num_len;
	int		sign;

	sign = ft_signed(n);
	num_len = sign + ft_numlen(n);
	result = (char *)malloc(sizeof(char) * (num_len + 1));
	if (!result)
		return (result);
	result[num_len] = '\0';
	if (sign)
	{
		*result = '-';
		result[--num_len] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (num_len-- - sign)
	{
		result[num_len] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
