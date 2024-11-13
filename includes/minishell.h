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
# include "readline/history.h"
# include "readline/readline.h"

# define SUCCESS 0
# define FAIL -1
# define ERROR 1
# define SYNTAX_ERROR 2
# define FPERM_DENIED 13
# define EXE_NOT_FOUND 125
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
	int			start;
	int			end;
	int			*protected;
	t_bool		in_dquotes;
	t_bool		in_squotes;
}				t_token;

typedef struct s_heredoc
{
	char		*fd_name[42];
	char		*delim;
	int			count;
	int			index;
	t_bool		in_quotes;
}				t_heredoc;

typedef struct s_fd
{
	char		*fdin;
	char		*fdout;
	int			saved_stdin;
	int			saved_stdout;
}				t_fd;

typedef struct s_pipes
{
	char		**p_args;
	int			**pipes;
	int			num_pipes;
	int			cmd_num;
}				t_pipes;

typedef struct s_minishell
{
	char		*cmd_path;
	char		**p_input;
	char		*input;
	char		*prompt_name;
	char		*user;
	char		*cwd;
	char		*prev_cwd;
	char		**history;
	char		**env;
	char		**tokens;
	char		**pretokens;
	int			tokc;
	int			std_in;
	int			std_out;
	int			std_err;
	int			ret;
	char		*path;
	t_token		token;
	t_heredoc	heredoc;
	t_fd		fd;
	t_bool		handled_heredoc;
	t_bool		interactive;
}				t_minishell;

// ft_signal_handler.c
void			init_signals_interactive(void);
void			reset_prompt(int sig);
void			handle_sigquit(void);
void			put_newline(int sig);
void			init_signals_noninteractive(void);

// is.c
int				ft_is_dquote(int c);
int				ft_is_squote(int c);
int				ft_isquotes(int c);
int				ft_ismeta_chars(int c);

// utils.c
int				count_tokens(char **tokens);
void			print_tokens(char **tokens);
char			**ft_envdup(char **envp);
int				wait_children(void);
void			print_debug(char **tokens);

// exit_minishell.c
void			exit_minishell(t_minishell *ms);
void			exit_child(t_minishell *ms);

// free.c
void			free_data(t_minishell *ms);
void			ft_free(void *ptr);
void			free_tokens(char **tokens);
void			free_at_address(char **str);
void			free_at_exit(t_minishell *ms);
void			free_int_array(int **arr);

// free_protected_array.c
void			free_protected_array(int **array);

// error.c
int				check_error(char *cmd);

// prompt_name.c
char			*get_prompt_name(t_minishell *ms);
char			*get_user_color(t_minishell *ms);
char			*get_arrow_color(t_minishell *ms, char *cwd_dup);
char			**get_cwdsplit(t_minishell *ms);


/* Tokenization */

// tokens_creator.c
int				tokens_creator(t_minishell *ms, char *line);
char			**transformer(t_minishell *ms);
void			fill_protected_arr(t_minishell *ms);
t_bool			is_only_spaces(char *line);

// tokenizer.c
int				separe_line(t_minishell *ms, char *line, int i, int *k);
char			**tokenizer(t_minishell *ms, char *line);
char			*meta_chars_extractor(char *line, int *i);

// quotes_detector.c
int				ft_quotes_detector(t_minishell *ms, char *line, int i);
int				ft_open_quotes_checker(t_minishell *ms, char *line);

// characterizer.c
char			**characterizer(t_minishell *ms, char **tokens);
char			*characterize_token(t_minishell *ms, char *token, int i);
char			*apply_nbr_expansion(t_minishell *ms, char *token_dup, int i);

// var_expansion.c
char			*apply_var_expansion(char *token_dup, int i);
char			*insert_variable_value(char *before, char *var, char *after);
char			*var_extractor(char *token, int *i);

// nbr_expansion.c
char			*apply_nbr_value(char *token_dup, int i, int nbr);
char			*insert_nbr_value(char *before, char *after, int nbr);
char			*single_var_extractor(char *token, int *i);

// trimmer.c
char			**trimmer(t_minishell *ms, char **tokens);
char			*ft_toktrim(t_minishell *ms, char *token, int len);

// has_meta.c
t_bool			has_redirect(t_minishell *ms, char **tokens);
t_bool			has_meta(t_minishell *ms, char **tokens);
t_bool			has_quotes(char *token);

// has_one_meta.c
t_bool			has_redirect_in(t_minishell *ms, char **tokens);
t_bool			has_redirect_out(t_minishell *ms, char **tokens);
t_bool			has_append(t_minishell *ms, char **tokens);
t_bool			has_heredoc(t_minishell *ms, char **tokens);
t_bool			has_pipe(t_minishell *ms, char **tokens);

// is_meta.c
t_bool			is_redirect(char *token);
t_bool			is_meta(char *token);

// is_one_meta.c
t_bool			is_redirect_in(char *token);
t_bool			is_redirect_out(char *token);
t_bool			is_append(char *token);
t_bool			is_heredoc(char *token);
t_bool			is_pipe(char *token);

// heredoc.c
int				execute_heredocs(t_minishell *ms);
int				exec_heredoc(t_minishell *ms);
int				heredoc(t_minishell *ms, char *delim);
void			fill_heredoc(t_minishell *ms, int fd, char *delim);
char			*create_heredoc_name(t_minishell *ms);

// heredoc_expander.c
char			*expand_line(t_minishell *ms, char *line);
char			*expander(t_minishell *ms, char *line);

// heredoc_utils.c
int				count_heredoc(t_minishell *ms);
int				shift_tokens(t_minishell *ms, int *index);
void			check_delim(t_minishell *ms, int pos);
t_bool			check_line(char *line, char *delim);

// heredoc_reset.c
void			unlink_heredocs(t_minishell *ms);
void			clear_heredoc_names(t_minishell *ms);
void			reset_heredoc(t_minishell *ms);

// heredoc_statics.c
void			reset_heredoc_statics(void);
int				update_heredoc_index(t_bool reset);
int				update_heredoc_number(t_bool reset);
int				update_heredoc_count(t_bool reset);

/* /commands */

// cd.c
int				cd(t_minishell *ms);
int				detect_cd_call(t_minishell *ms);

// pwd.c
int				pwd(t_minishell *ms);
int				detect_pwd_call(t_minishell *ms);

// echo.c
void			echo(char **tokens, int opt);
void			echo_n(char **tokens);
int				detect_echo_call(t_minishell *ms);

// executable.c
int				detect_executable(t_minishell *ms);

// env.c
int				detect_env_call(t_minishell *ms);
int				env(t_minishell *ms);

// exit.c
t_bool			is_exit(char *token);

// find_executable_path.c
char			*get_path(char *cmds);
char			*create_full_path(char *dir, char *cmds);
char			*get_last_dir(char *cmds);

// commands.c
int				call_commands(t_minishell *ms);
int				ft_execvp(char **tokens, char **envp);
int				exec_builtin(t_minishell *ms);
int				built_in_cmds(t_minishell *ms);

// redirection.c
int				exec_redirection(t_minishell *ms);
void			recreate_tokens(t_minishell *ms, int i);
int				redirect_input(char *file);
int				redirect_output(char *file);
int				append_output(char *file);

// ft_pipes

int				has_pipes(t_minishell *ms, char **str);
int				count_pipes(t_minishell *ms, char **str);
int				**allocate_pipes(t_pipes *p);
char			**extract_args(char **tokens, int start, int end);
void			close_pipes(t_pipes *p);
void			pipes_redirection(t_pipes *p);
int				exect_pipes(t_minishell *ms);
int				create_and_manage_process(t_minishell *ms, t_pipes *p,
					pid_t *pid);
void			handle_child_process(t_minishell *ms, t_pipes *p);
void			tokenize_input1(t_minishell *ms);
int				call_commands_pipes(t_minishell *ms, t_pipes *p);
int				exec_redirection_pipes(t_pipes *p);
void			recreate_pipes_args(t_pipes *p, int i);

#endif
