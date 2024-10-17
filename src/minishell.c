/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:14:08 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/15 17:06:53 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* init the minishell struct variables */
void	ft_init_minishell(t_minishell *ms)
{
	ft_bzero(ms, sizeof(*ms));
	ms->prompt = NULL;
	ms->prompt_name = NULL;
	ms->user = NULL;
	ms->cwd = NULL;
	ms->env = NULL;
	ms->tokens = NULL;
	ms->pretokens = NULL;
	ms->tokc = 0;
	ms->std_in = 0;
	ms->std_out = 1;
	ms->std_err = 2;
	ms->token.end = 0;
	ms->token.start = 0;
	ms->token.in_dquotes = FALSE;
	ms->token.in_squotes = FALSE;
	ms->token.in_quotes = FALSE;
}

/*
	Create the prompt name by joining the username with the current working
	directory found in the environment variables. For using color, I joined a
	empty string with the username, then a '/', and finally the directory. Since
	cwd return a full path (/home/username/folder/) , I splited the directory
	when we find a '/', then got the last directory to get it displayed next
	to the name. I reused a Macro to make the arrow green, which is showing
	after the name and directory. Finally I return this result, so we get a
	pretty cool prompt name ! If we got a problem and didnt get a name or a
	directory, we return a default name to avoid segmentation fault or empty
	prompt name.
*/
char	*ft_get_prompt_name(char *username, char *cwd)
{
	char	*username_dup;
	char	*color;
	char	*cwd_dup;
	char	**cwd_split;
	char	*tmp;

	cwd_split = ft_split(cwd, '/');
	if (username && cwd)
	{
		color = ft_strjoin(CYAN BOLD "", username);
		tmp = color;
		color = ft_strjoin(color, "/");
		ft_free(tmp);
		cwd_dup = ft_strjoin(color, cwd_split[ft_count_tokens(cwd_split) - 1]);
		username_dup = ft_strjoin(cwd_dup, GREEN " ➜  " RESET BOLDRESET);
		ft_free(color);
		ft_free(cwd_dup);
		ft_free_tokens(cwd_split);
		return (username_dup);
	}
	else
		ft_free_tokens(cwd_split);
	return ("minishell ➜ ");
}

/*
	Dup the environment string tab
	to do: need to check if we can use it to remove a variable
	with unset and re-add it with export. I didn't try yet.
*/
char	**ft_envdup(char **envp)
{
	char	**env_dup;
	int		i;
	int		j;
	int		size;

	size = ft_count_tokens(envp);
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

/*
	Execute the prompt in a loop and read the input with readline,
	then separe the string in token , search the path and execute the command
	if the path is found. Add_history allow us to click the up arrow key to
	reuse a command. It frees the input after each line so we don't have leaks
	or corrupted data.
*/
void	ft_execms(t_minishell *ms, char **envp)
{
	while (1)
	{
		ft_init_minishell(ms);
		ms->env = ft_envdup(envp);
		ms->user = getenv("USER");
		ms->cwd = getcwd(NULL, 0);
		ms->prompt_name = ft_get_prompt_name(ms->user, ms->cwd);
		ms->prompt = readline(ms->prompt_name);
		// for (size_t i = 0; i < ft_strlen(ms->prompt); i++)
		// {
		// 	printf("%i\n", ms->prompt[i]);
		// }
		
		if (!ms->prompt)
		{
			ft_exit_minishell(ms);
			break ;
		}
		if (*(ms->prompt) != '\0')
			parse_prompt(ms, ms->prompt);
		ft_free2(&ms->prompt);
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
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	if (argc == 1)
		ft_execms(ms, envp);
	free(ms);
	return (0);
}
/*
108
115
32
45
108
32
124
32
108
115
32
45
108
*/