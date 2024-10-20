/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:08:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/20 13:06:58 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <locale.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SUCCESS 0
# define FAIL -1
# define ERROR 1
# define SYNTAXE_ERROR 2
# define FPERM_DENIED 13
# define CPERM_DENIED 126
# define CMD_NOT_FOUND 127
# define TERM_SIGINT 130
# define TERM_SIGKILL 137
# define SEGFAULT 139

# define SURL "\e[7m"
# define SURLRESET "\e[0m"

# define BOLD "\033[1m"
# define BOLDRESET "\033[0m"

# define MB_SIZE 2097152
# define SIZE_CHAR_PTR sizeof(char *)

# define MAX_PATH 4096

typedef struct s_token
{
	char	start;
	char	end;
	t_bool	in_dquotes;
	t_bool	in_squotes;
}			t_token;

typedef struct s_minishell
{
	char	*input;
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
	int		ret;
	int		pid;
}			t_minishell;

// ft_signal_handler.c
void		ft_init_sigaction(void);
void		ft_signal_handler(int sig, siginfo_t *siginfo, void *context);

// ft_if_is.c
int			ft_is_dquote(int c);
int			ft_is_squote(int c);
int			ft_isquotes(int c);
int			ft_isredirect(int c);

// ft_utils.c
int			ft_count_tokens(char **tokens);
void		ft_print_tokens(char **tokens);
char		**ft_envdup(char **envp);
int			wait_children(t_minishell *ms);

// ft_exit.c
void		exit_minishell(t_minishell *ms);
void		exit_child(t_minishell *ms);

// ft_free.c
void		ft_free_vars(t_minishell *ms);
void		ft_free(char *str);
void		ft_free_tokens(char **tokens);
void		ft_free2(char **str);
void		ft_free_at_exit(t_minishell *ms);

// ft_error.c
int			check_error(t_minishell *ms, char *cmd);

// ft_display.c
char		*get_user_color(t_minishell *ms, char *username);
char		*get_arrow_color(t_minishell *ms, char *cwd_dup);

/* /lexing */

// redirection.c
void		ft_exec_redirection(t_minishell *ms);
void		ft_recreate_tokens(t_minishell *ms, int i);
void		redirect_input(t_minishell *ms, char *file);
void		redirect_output(t_minishell *ms, char *file);

// tokens_creator.c
int			tokens_creator(t_minishell *ms, char *line);

// tokenizer.c
int			separe_line(t_minishell *ms, char *line, int i, int k);
char		**tokenizer(t_minishell *ms, char *line);
int			ft_quotes_detector(t_minishell *ms, char *line, int i);
int			ft_open_quotes_checker(t_minishell *ms, char *line);

// characterizer.c
char		**characterizer(t_minishell *ms, char **tokens);
char		*characterize_token(t_minishell *ms, char *token, int i);
char		*var_extractor(char *token, int *i);
char		*insert_variable_value(char *before, char *var, char *after);

// var_expansion.c
char		*apply_var_expansion(char *token_dup, int i);
char		*ret_var_extractor(char *token, int *i);
char		*insert_return_value(t_minishell *ms, char *before, char *after);
char		*apply_return_value(t_minishell *ms, char *token_dup, int i);

// trimmer.c
char		**trimmer(t_minishell *ms, char **tokens);
char		*ft_toktrim(t_minishell *ms, char *token, int len);

/* /commands */

// cd.c
int			cd(t_minishell *ms, int k);
int			detect_cd_call(t_minishell *ms, int k);

// pwd.c
int			pwd(t_minishell *ms, int k);
int			detect_pwd_call(t_minishell *ms, int k);

// echo.c
void		echo(char **tokens);
void		echo_n(char **tokens);
int			detect_echo_call(t_minishell *ms, int k);

// executable.c
int			detect_executable(t_minishell *ms, int k);

// env.c
int			detect_env_call(t_minishell *ms, int k);
int			env(t_minishell *ms, int k);

// find_executable_path.c
char		*find_executable_path(char *cmds);
char		*create_full_path(char *dir, char *cmds);
char		*get_last_dir(char *cmds);

// commands.c
int			parse_input(t_minishell *ms, char *input);
int			call_commands(t_minishell *ms);
int			exec_path_cmds(t_minishell *ms, char **tokens, int i);
int			external_cmds(t_minishell *ms);
int			built_in_cmds(t_minishell *ms);

#endif
