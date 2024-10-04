/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:16:44 by ccodere           #+#    #+#             */
/*   Updated: 2024/02/28 13:16:44 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putbase(long n, int base)
{
	int		count;
	char	*characters;

	count = 0;
	characters = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_putbase(-n, base) + 1);
	}
	else if (n < base)
	{
		return (ft_putchar(characters[n]));
	}
	else
	{
		count = ft_putbase(n / base, base);
		return (count + ft_putbase(n % base, base));
	}
}
