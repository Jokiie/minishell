/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:52:01 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 03:06:39 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**recreate_tokens(char **tokens, int **protected, int count, t_bool in_pipe)
{
	char	**new_tokens;
	int		*new_protected;
	int		i;
	int		j;
	
	(void)in_pipe;
    new_protected = malloc(sizeof(int) * (count + 1));
    if (!new_protected)
	    return (NULL);
	new_tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_tokens)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i] && j < count)
	{
		while ((is_redirect(tokens[i]) || is_heredoc(tokens[i])) && (*protected)[i] == 0)
		{
			i += 2;
		}
		if (!tokens[i])
			break ;
		new_tokens[j] = ft_strdup(tokens[i]);
		new_protected[j] = (*protected)[i];
		j++;
		i++;
	}
	new_tokens[j] = NULL;
	new_protected[j] = '\0';
	free(*protected);
	*protected = new_protected;
	return (new_tokens);
}

int	get_filtered_tokc(char **tokens, int **protected)
{
	int	count;
	int	i;

	i = 0;
	count = count_tokens(tokens);
	while (tokens[i])
	{
		if ((is_redirect(tokens[i]) || is_heredoc(tokens[i])) && (*protected)[i] == 0)
		{
			count = count - 2;
		}
		i++;
	}
	if (count == 0)
		return (0);
	return (count);
}

int	cat_heredoc(char *file)
{
	int		fd;
	char	*line;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "ms: %s: %s\n", strerror(errno), file);
		return (FAIL);
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);	
}
