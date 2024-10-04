/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:22:22 by ccodere           #+#    #+#             */
/*   Updated: 2024/03/03 22:37:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_parse_pointer(va_list args)
{
	int						count;
	unsigned long			ptr;
	char					buffer[20];
	char					*array;

	count = 0;
	ptr = (unsigned long)va_arg(args, void *);
	if (ptr == '\0')
		count += ft_putstr("0x0");
	else
	{
		array = ft_itoa_base(ptr, buffer, 16);
		count += ft_putstr("0x") + ft_putstr(array);
	}
	return (count);
}

int	ft_parse_chars(char format, va_list args)
{
	int	count;

	count = 0;
	if (format == '\0')
		return (-1);
	if (format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_parse_digits(char format, va_list args)
{
	int		count;

	count = 0;
	if (format == '\0')
		return (-1);
	if (format == 'd' || format == 'i')
	{
		if (format == '0' && ((format + 1) == 'x' || (format + 1) == 'X'))
			count += ft_putbase_hex((long)(va_arg(args, unsigned int)), 0);
		else if (format == '0')
			count += ft_putbase((long)(va_arg(args, unsigned int)), 8);
		else
			count += ft_putbase((long)(va_arg(args, int)), 10);
	}
	else if (format == 'u')
		count += ft_putbase((long)(va_arg(args, unsigned int)), 10);
	else if (format == 'x')
		count += ft_putbase_hex((long)(va_arg(args, unsigned int)), 0);
	else if (format == 'X')
		count += ft_putbase_hex((long)(va_arg(args, unsigned int)), 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;

	va_start(args, format);
	count = 0;
	if (format == NULL)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c' || *format == 's' || *format == '%')
				count += ft_parse_chars(*format, args);
			else if (*format == 'p')
				count += ft_parse_pointer(args);
			else
				count += ft_parse_digits(*format, args);
		}
		else
			count += ft_putchar(*format);
		++format;
	}
	va_end(args);
	return (count);
}
