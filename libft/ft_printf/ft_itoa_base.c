/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:16:22 by ccodere           #+#    #+#             */
/*   Updated: 2024/02/28 13:16:22 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_itoa_base(unsigned long value, char *buffer, int base)
{
	const char		*chars;
	char			*array;
	unsigned long	temp;
	int				len;

	chars = "0123456789abcdef";
	array = buffer;
	temp = value;
	len = 0;
	while (temp != 0)
	{
		temp /= base;
		len++;
	}
	array += len;
	*array = '\0';
	while (value != 0)
	{
		--array;
		*array = chars[value % base];
		value /= base;
	}
	return (array);
}
