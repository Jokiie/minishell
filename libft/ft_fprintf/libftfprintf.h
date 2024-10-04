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

#ifndef LIBFTFPRINTF_H
# define LIBFTFPRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft.h"
# include "fcntl.h"

char	*ft_fitoa_base(unsigned long value, char *buffer, int base);
int		ft_fputchar(int fd, int c);
int		ft_fputstr(int fd, char *str);
int		ft_fputbase(int fd, long n, int base);
int		ft_fputbase_hex(int fd, long n, int uppercase);
int		ft_fprintf(int fd, const char *format, ...);
#endif
