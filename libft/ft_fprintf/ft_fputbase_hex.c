/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:16:39 by ccodere           #+#    #+#             */
/*   Updated: 2024/02/28 13:16:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

int	ft_fputbase_hex(int fd, long n, int uppercase)
{
	int		count;
	char	*base;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n < 0)
	{
		n = (unsigned int)-n;
		return (ft_fputbase_hex(fd, n / 16, uppercase) + 1);
	}
	else if (n < 16)
	{
		return (ft_fputchar(fd, base[n]));
	}
	else
	{
		count = ft_fputbase_hex(fd, n / 16, uppercase);
		return (count + ft_fputbase_hex(fd, n % 16, uppercase));
	}
}
