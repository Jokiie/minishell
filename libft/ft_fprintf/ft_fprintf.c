/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:22:22 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/25 22:07:13 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

int	ft_fparse_pointer(int fd, va_list args)
{
	int						count;
	unsigned long			ptr;
	char					buffer[20];
	char					*array;

	count = 0;
	ptr = (unsigned long)va_arg(args, void *);
	if (ptr == '\0')
		count += ft_fputstr(fd, "0x0");
	else
	{
		array = ft_fitoa_base(ptr, buffer, 16);
		count += ft_fputstr(fd, "0x") + ft_fputstr(fd, array);
	}
	return (count);
}

int	ft_fparse_chars(int fd, char format, va_list args)
{
	int	count;

	count = 0;
	if (format == '\0')
		return (-1);
	if (format == 'c')
		count += ft_fputchar(fd, va_arg(args, int));
	else if (format == 's')
		count += ft_fputstr(fd, va_arg(args, char *));
	else if (format == '%')
		count += ft_fputchar(fd, '%');
	return (count);
}

int	ft_fparse_digits(int fd, char format, va_list args)
{
	int		count;

	count = 0;
	if (format == '\0')
		return (-1);
	if (format == 'd' || format == 'i')
	{
		if (format == '0' && ((format + 1) == 'x' || (format + 1) == 'X'))
			count += ft_fputbase_hex(fd, (long)(va_arg(args, unsigned int)), 0);
		else if (format == '0')
			count += ft_fputbase(fd, (long)(va_arg(args, unsigned int)), 8);
		else
			count += ft_fputbase(fd, (long)(va_arg(args, int)), 10);
	}
	else if (format == 'u')
		count += ft_fputbase(fd, (long)(va_arg(args, unsigned int)), 10);
	else if (format == 'x')
		count += ft_fputbase_hex(fd, (long)(va_arg(args, unsigned int)), 0);
	else if (format == 'X')
		count += ft_fputbase_hex(fd, (long)(va_arg(args, unsigned int)), 1);
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
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
				count += ft_fparse_chars(fd, *format, args);
			else if (*format == 'p')
				count += ft_fparse_pointer(fd, args);
			else
				count += ft_fparse_digits(fd, *format, args);
		}
		else
			count += ft_fputchar(fd, *format);
		++format;
	}
	va_end(args);
	return (count);
}
