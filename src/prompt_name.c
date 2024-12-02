/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:35:20 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/02 03:06:43 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Create the prompt name by joining the username with the current working
	directory found in the environment variables. For using color, we joined a
	empty string with the username, then a '/', and finally the directory. Since
	cwd return a full path (/home/username/folder/) , we splited the directory
	when we find a '/', then got the last directory to get it displayed next
	to the name. We reused a Macro to make the arrow green, which is showing
	after the name and directory. Finally we return this result, so we get a
	pretty cool prompt name ! If we got a problem and didnt get a name or a
	directory, we return a default name to avoid segmentation fault or empty
	prompt name.
*/
char	*get_prompt_name(t_minishell *ms)
{
	char	*username_dup;
	char	*color;
	char	*cwd_dup;
	char	**split;
	char	*tmp;

	split = get_cwdsplit(ms);
	if (split && *split)
	{
		color = get_user_color(ms);
		tmp = color;
		color = ft_strjoin(color, "/");
		free_ptr(tmp);
		cwd_dup = ft_strjoin(color, split[count_tokens(split) - 1]);
		username_dup = get_arrow_color(ms, cwd_dup);
		free_ptr(color);
		free_ptr(cwd_dup);
	}
	else
		username_dup = ft_strdup(CYAN BOLD "minishell ➜  " RESET BOLDRESET);
	free_tokens(split);
	return (username_dup);
}

char	**get_cwdsplit(t_minishell *ms)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = NULL;
	ms->cwd = getcwd(NULL, 0);
	if ((ms->cwd[0] == '/' && !ms->cwd[1]) || (ms->cwd[1] && ms->cwd[1] == '/'))
	{
		while (ms->cwd[i] && ms->cwd[i] == '/')
			i++;
		if (!ms->cwd[i])
			splitted = ft_split("'/'/'/'", '\'');
		return (splitted);
	}
	splitted = ft_split(ms->cwd, '/');
	return (splitted);
}

char	*get_arrow_color(t_minishell *ms, char *cwd_dup)
{
	char	*arrow_color;

	arrow_color = NULL;
	if (ms->ret == 0)
		arrow_color = ft_strjoin(cwd_dup, GREEN " ➜  " RESET BOLDRESET);
	else
		arrow_color = ft_strjoin(cwd_dup, RED " ➜  " RESET BOLDRESET);
	return (arrow_color);
}

char	*get_user_color(t_minishell *ms)
{
	char	*color;

	ms->user = get_env(ms->env, "USER");
	color = NULL;
	if (ft_strncmp(ms->user, "ccodere", 7) == 0)
	{
		ms->user = "Celia";
		color = ft_strjoin(MAGENTA BOLD "", ms->user);
	}
	else if (ft_strnstr(ms->user, "matis", ft_strlen(ms->user)))
	{
		ms->user = "Matis";
		color = ft_strjoin(GREEN BOLD "", ms->user);
	}
	else if (!ms->user)
	{
		ms->user = "Human";
		color = ft_strjoin(YELLOW BOLD "", ms->user);
	}
	else
	{
		color = ft_strjoin(CYAN BOLD "", ms->user);
	}
	return (color);
}

char	*get_last_dir(char *path)
{
	char	**dir_split;
	char	*last_dir;
	int		dir_count;

	dir_split = ft_split(path, '/');
	dir_count = count_tokens(dir_split);
	last_dir = ft_strdup(dir_split[dir_count - 1]);
	free_tokens(dir_split);
	return (last_dir);
}
