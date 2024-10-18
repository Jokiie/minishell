/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:18:05 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/18 13:42:41 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "commands.h"

/*
	Iterate in the paths returned by ft_strtok to find where is the cmd process
	to execute. ft_strtok() replace the delimiter(here ':') by a null character,
	creating tokens. We recall ft_strtok with NULL, to continue with the next
	token. If we find a match, and we can access it, we return the path to
	execute.

	to do:
		paths = (should search in ms->env), not with getenv ?
*/
char	*find_executable_path(char *cmds)
{
	char	*paths;
	char	*paths_dup;
	char	*dir;
	char	*full_path;

	paths = getenv("PATH");
	paths_dup = ft_strdup(paths);
	if (!paths_dup)
		return (NULL);
	dir = ft_strtok(paths_dup, ":");
	while (dir != NULL)
	{
		full_path = create_full_path(dir, cmds);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free(paths_dup);
			return (full_path);
		}
		dir = ft_strtok(NULL, ":");
		if (full_path)
			ft_free(full_path);
	}
	ft_free(paths_dup);
	return (NULL);
}

/*
	We append the name of the command to the directory in parameter.
	The result will be the full path of the command to search a match
	in the function "find_executable_path".
	example :
	we typed "ls" in the command line :
	find_executable_path extracted the path "/usr/bin" from PATH
	the current directory to check is "/usr/bin"
	create_full_path append "/usr/bin" with '/' then append the cmd "ls". The
	result will be "/usr/bin/ls". We return this result to find_executable_path
	so we can check if this path is accessible, if yes, we return this path to
	exerve in exec_path_cmds().
*/
char	*create_full_path(char *dir, char *cmds)
{
	char	*full_path;

	full_path = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	ft_strlcpy(full_path, dir, BUFFER_SIZE);
	ft_strlcat(full_path, "/", BUFFER_SIZE);
	ft_strlcat(full_path, cmds, BUFFER_SIZE);
	return (full_path);
}

/*
	Handle the case of absolute path token (like /usr/bin/ls"). We split
	the string with the '/' as delimiter, then return the last element as a
	command, because we want to use it to iterate in the directories, like if
	we typed "ls".
*/
char	*get_last_dir(char *cmds)
{
	char	**dir_split;
	char	*last_dir_dup;
	int		dir_count;

	dir_split = ft_split(cmds, '/');
	dir_count = ft_count_tokens(dir_split);
	last_dir_dup = ft_strdup(dir_split[dir_count - 1]);
	ft_free_tokens(dir_split);
	return (last_dir_dup);
}
