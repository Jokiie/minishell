/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:17:18 by ccodere           #+#    #+#             */
/*   Updated: 2024/02/28 13:17:18 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft.h"

char	*ft_itoa_base(unsigned long value, char *buffer, int base);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putbase(long n, int base);
int		ft_putbase_hex(long n, int uppercase);
int		ft_printf(const char *format, ...);
#endif
