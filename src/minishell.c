
#include "../includes/minishell.h"

/* init the minishell struct variables */
void	ft_init_minishell(t_minishell *ms)
{
	ms->input = NULL;
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
	ms->ret = 0;
	ms->pid = getpid();
}

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
char	*ft_get_prompt_name(t_minishell *ms, char *username, char *cwd)
{
	char	*username_dup;
	char	*color;
	char	*cwd_dup;
	char	**cwd_split;
	char	*tmp;

	if (cwd)
		cwd_split = ft_split(cwd, '/');
	if (cwd)
	{
		color = get_user_color(ms, username);
		tmp = color;
		color = ft_strjoin(color, "/");
		ft_free(tmp);
		cwd_dup = ft_strjoin(color, cwd_split[ft_count_tokens(cwd_split) - 1]);
		username_dup = get_arrow_color(ms, cwd_dup);
		ft_free(color);
		ft_free(cwd_dup);
		ft_free_tokens(cwd_split);
		return (username_dup);
	}
	return (ft_strdup(CYAN BOLD "minishell ➜  " RESET BOLDRESET));
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
	ms->env = ft_envdup(envp);
	// rl_bind_key('\t', rl_complete);
	while (1)
	{
		ms->user = getenv("USER");
		ms->cwd = getcwd(NULL, 0);
		ms->prompt_name = ft_get_prompt_name(ms, ms->user, ms->cwd);
		ms->input = readline(ms->prompt_name);
		if (!ms->input)
		{
			exit_minishell(ms);
			break ;
		}
		if (*(ms->input) != '\0')
		{
			ms->ret = parse_input(ms, ms->input);
			add_history(ms->input);
		}
		ft_free_vars(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		exit_minishell(ms);
	ft_memset(ms, 0, sizeof(ms));
	(void)argv;
	if (argc == 1)
	{
		ft_init_minishell(ms);
		ft_init_sigaction();
		ms->pid = getpid();
		ft_execms(ms, envp);
	}
	exit_minishell(ms);
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