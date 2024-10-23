/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:08:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/22 17:27:50 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "readline/history.h"
# include "readline/readline.h"

# define SUCCESS 0
# define FAIL 1
# define ERROR -1

# define SURL "\e[7m"
# define SURLRESET "\e[0m"

# define BOLD "\033[1m"
# define BOLDRESET "\033[0m"

# define MB_SIZE 2097152
# define PTR_SIZE sizeof(char *)

# define MAX_PATH 4096

typedef struct s_token
{
	char	start;
	char	end;
	t_bool	in_dquotes;
	t_bool	in_squotes;
	t_bool	in_quotes;
	t_bool	open_dquotes;
	t_bool	open_squotes;
}			t_token;

typedef struct s_minishell
{
	char	*prompt;
	char	*prompt_name;
	char	*user;
	char	*cwd;
	char	**history;
	char	**env;
	char	**tokens;
	char	**pretokens;
	int		tokc;
	int		std_in;
	int		std_out;
	int		std_err;
	t_token	token;
}			t_minishell;


// ft_signal_handler.c

void		ft_sigint_handler(int sig);
void		ft_sigquit_handler(int sig);

// ft_commands.c
void		parse_prompt(t_minishell *ms, char *prompt);
void		call_commands(t_minishell *ms);
int			exec_cmd_in_paths(t_minishell *ms, char **tokens, int i);
int			external_cmds(t_minishell *ms);
int			built_in_cmds(t_minishell *ms);

// ft_check_cmd_path.c
char		*ft_create_full_path(char *dir, char *cmds);
char		*ft_get_last_dir(char *cmds);
char		*ft_create_n_check_path(char *cmds);

// trimmer.c
char		**trimmer(t_minishell *ms, char **tokens);
char		*ft_toktrim(t_minishell *ms, char *token, int len);

// characterizer.c
char		**characterizer(t_minishell *ms, char **tokens);
char		*characterize_token(t_minishell *ms, char *token, int i);
char		*check_quotes(t_minishell *ms, char c);
char		*var_extractor(char *token, int *i);
char		*insert_variable_value(char *before, char *var, char *after);

// redirection.c
void		ft_exec_redirection(t_minishell *ms);
void		ft_recreate_tokens(t_minishell *ms, int i);
void		redirect_input(t_minishell *ms, char *file);
void		redirect_output(t_minishell *ms, char *file);

char		*apply_var_expansion(char *token_dup, int i);

// tokenizer.c
int			separe_line(t_minishell *ms, char *line, int i, int k);
char		**tokenizer(t_minishell *ms, char *line);
int			ft_create_tokens(t_minishell *ms, char *line);

// ft_if_is.c
int			ft_is_dquote(int c);
int			ft_is_squote(int c);
int			ft_isquotes(int c);
int			ft_isredirect(int c);

// ft_utils.c
int			ft_count_tokens(char **tokens);
void		ft_print_tokens(char **tokens);

// ft_exit.c
void		ft_exit_minishell(t_minishell *ms);

// ft_free.c
void		ft_free_vars(t_minishell *ms);
void		ft_free(char *str);
void		ft_free_tokens(char **tokens);
void		ft_free2(char **str);
void		ft_free_vars2(t_minishell *ms);

char		**ft_envdup(char **envp);

//ft_pipes
int		ft_has_pipe(char *str);
int		ft_count_pipes(char **str);
int		**ft_allocate_pipes(int num_pipes);
char	**ft_extract_args(char **tokens, int start, int end);
void	ft_close_pipes(int **pipes, int num_pipes);
void	ft_pipes_redirection(int **pipes, int cmd_num, int num_pipes);
int		ft_exect_pipes(t_minishell *ms);

#endif
