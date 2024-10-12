/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:33:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 02:36:28 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

void	ft_free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	ft_charcount(char *line, char to_count)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == to_count)
			count++;
		i++;
	}
	return (count);
}

char	*ft_strpass(char *str, int to_pass, int len)
{
	char	*buffer;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < len)
	{
		if (str[i] != to_pass)
			buffer[j++] = str[i];
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

char	*ft_strskip(char *str, char *to_pass, int len)
{
	char	*buffer;
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < len)
	{
		k = 0;
		while (to_pass[k])
		{
			if (str[i] != to_pass[k])
				buffer[j++] = str[i];
			k++;
		}
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}
