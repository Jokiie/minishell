/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:29:15 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/20 16:36:58 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Iterate in the paths returned by ft_strtok to find where is the cmd process
	to execute. ft_strtok() replace the delimiter(here ':') by a null character,
	creating tokens. We recall ft_strtok with NULL, to continue with the next
	token. If we find a match, and we can access it, we return the path to
	execute.
	to do:
		paths = (should search in ms->env), not with getenv ?
*/
char	*get_path(char **envp, char *cmds)
{
	char	*paths;
	char	*paths_dup;
	char	*dir;
	char	*full_path;

	paths = get_env(envp, "PATH");
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
