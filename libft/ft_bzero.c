/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:58:25 by ccodere           #+#    #+#             */
/*   Updated: 2024/03/07 09:51:41 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Example
// char str[13] = "Hello World!";
// ft_bzero(str, 13);
void	ft_bzero(void *str, size_t len)
{
	unsigned char	*str_ptr;

	if (len == 0)
		return ;
	str_ptr = (unsigned char *)str;
	while (str != NULL && len--)
		*str_ptr++ = 0;
}
