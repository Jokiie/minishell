/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:15:55 by ccodere           #+#    #+#             */
/*   Updated: 2024/02/28 13:15:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

int	ft_fputstr(int fd, char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (write(fd, "(null)", 6));
	while (*str != '\0')
	{
		ft_fputchar(fd, (int)*str);
		++count;
		++str;
	}
	return (count);
}
