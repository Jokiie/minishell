/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:14:08 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 12:46:53 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /!\ Do not delete realine.supp /!\
// To check if we have leaks while ignoring the leaks from readline : 
// valgrind --child-silent-after-fork=yes --leak-check=full --suppressions=readline.supp ./minishell
 
/* init the minishell struct variables */
void	ft_init_minishell(t_minishell *ms)
{
	ms->prompt = NULL;
	ms->prompt_name = NULL;
	ms->user = NULL;
	ms->cwd = NULL;
	ms->env = NULL;
	ms->args = NULL;
	ms->argc = 0;
	ms->std_in = 0;
	ms->std_out = 1;
	ms->std_err = 2;
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
}
/*  Create the prompt name, I did it for fun */
char	*ft_get_prompt_name(char *username, char *cwd)
{
	char	*username_dup;
	char	*color;
	char	*cwd_dup;
	char	**cwd_split;
	char	*tmp;
	int		last_dir;

	cwd_split = ft_split(cwd, '/');
	last_dir = ft_count_args(cwd_split) - 1;
	if (username && cwd)
	{
		color = ft_strjoin(CYAN BOLD "", username);
		tmp = color;
		color = ft_strjoin(color, "/");
		free(tmp);
		cwd_dup = ft_strjoin(color, cwd_split[last_dir]);
		username_dup = ft_strjoin(cwd_dup, GREEN " ➜  " RESET BOLDRESET);
		free(color);
		free(cwd_dup);
		ft_free_split(cwd_split);
		return (username_dup);
	}
	else
		ft_free_split(cwd_split);
	return ("minishell ➜ ");
}

/* Dup the env string list, need to check if we can use it to remove a variable with unset and re-add it with export */
char	**ft_envdup(char **envp)
{
	char	**env_dup;
	int		i;
	int		j;
	int		size;

	size = ft_count_args(envp);
	env_dup = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_dup)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i] && j < (size + 1))
		env_dup[j++] = ft_strdup(envp[i++]);
	env_dup[j] = NULL;
	return (env_dup);
}

/* Execute the prompt in a loop and read the input with readline, then separe the string in token , search the path and execute the command if the path is found. */
int	ft_execms(t_minishell *ms, char **envp)
{
	while (1)
	{
		ft_init_minishell(ms);
		ms->env = ft_envdup(envp);
		ms->user = getenv("USER");
		ms->cwd = getcwd(NULL, 0);
		ms->prompt_name = ft_get_prompt_name(ms->user, ms->cwd);
		ms->prompt = readline(ms->prompt_name);
		ft_init_token(ms, ms->prompt, 0, 0);
		ft_call_commands(ms->args, envp);
		if (ms->prompt == NULL)
			ft_exit_minishell(ms);
		if (*(ms)->prompt)
			add_history(ms->prompt);
		ft_free_vars(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	(void)argv;
	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		ft_exit_minishell(ms);
	if (argc == 1)
		ft_execms(ms, envp);
	return (0);
}
