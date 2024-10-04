/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:28:14 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 13:36:49 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_create_full_path(char *dir, char *cmds)
{
	char *full_path;

	full_path = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	ft_strlcpy(full_path, dir, BUFFER_SIZE);
	ft_strlcat(full_path, "/", BUFFER_SIZE);
	ft_strlcat(full_path, cmds, BUFFER_SIZE);
	return (full_path);
}

char	*ft_get_last_dir(char *cmds)
{
	char	**dir_split;
	char	*last_dir_dup;
	int		dir_count;
	
	dir_split = ft_split(cmds, '/');
	dir_count = ft_count_args(dir_split);
	last_dir_dup = ft_strdup(dir_split[dir_count - 1]);
	ft_free_split(dir_split);
	return (last_dir_dup);
}

char	*ft_create_n_check_path(char *cmds)
{
	char	*paths;
	char	*paths_dup;
	char	*dir;
	char	*full_path;
	
	paths = getenv("PATH");
	paths_dup = ft_strdup(paths);
	dir = ft_strtok(paths_dup, ":");
	while (dir != NULL)
	{
		full_path = ft_create_full_path(dir, cmds);
		if (access(full_path, X_OK) == 0)
		{
			free(paths_dup);
			return (full_path);
		}
		dir = ft_strtok(NULL, ":");
	}
	ft_fprintf(2, "minishell : command not found : %s\n", cmds);
	free(full_path);
	free(paths_dup);
	return (NULL);
}
