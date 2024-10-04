/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:25:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/25 15:27:45 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*_append(char *remainder, char *buffer)
{
	char	*copy;

	if (!remainder)
		remainder = ft_strdup("");
	copy = remainder;
	remainder = ft_strjoin(copy, buffer);
	free(copy);
	copy = NULL;
	return (remainder);
}

static char	*_read_n_append(int fd, char *remainder, char *buffer)
{
	ssize_t	chars_read;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(remainder);
			return (0);
		}
		else if (chars_read == 0)
			break ;
		buffer[chars_read] = '\0';
		remainder = _append(remainder, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remainder);
}

static char	*_extract_remainder(char *line, char *remainder)
{
	char	*newline;
	ssize_t	i;

	i = 0;
	newline = ft_strchr(line, '\n');
	while (line[i] != '\n')
	{
		if (line[i] == '\0')
			return (0);
		i++;
	}
	if (newline)
		remainder = ft_strdup(newline + 1);
	else
		remainder = ft_strdup("");
	if (!*remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	line[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
	{
		free(buffer);
		free(remainder);
		buffer = NULL;
		remainder = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = _read_n_append(fd, remainder, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder = _extract_remainder(line, remainder);
	return (line);
}
