#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <locale.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
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
	int			*isheredoc;
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
	int			cmd_start;
	t_bool		last_cmd;
	int			ret;
	int			*arg_protected;
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

	char		**test;

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
	t_bool		interactive;
	t_pipes		p;
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
void			exit_minishell(t_minishell *ms, int return_code);
void			exit_child(t_minishell *ms, int return_code);

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

// syntax_error.c
int				check_syntax(char **tokens);
int				errors_redirect(char **tokens);
int				error_pipes(char **tokens);

// contains_only.c
t_bool			contains_only_digits(char *line);
t_bool			contains_only_spaces(char *line);
t_bool			contains_heredoc(t_minishell *ms);

/* /commands */

// cd.c
int				cd(char **tokens);
int				detect_cd_call(char **tokens);

// pwd.c
int				pwd(t_minishell *ms);
int				detect_pwd_call(t_minishell *ms, char **tokens);

// echo.c
void			echo(t_minishell *ms, char **tokens, int opt);
int				detect_echo_call(t_minishell *ms, char **tokens);

// executable.c
int				detect_executable(t_minishell *ms, char **tokens);
int				check_error_executable(char *executable);

// env.c
int				detect_env_call(t_minishell *ms, char **tokens);
int				env(t_minishell *ms, char **tokens);

// exit.c
int				detect_exit_call(t_minishell *ms, char **tokens, int is_child);
int				ft_exit(t_minishell *ms, char **tokens, int is_child);

// get_path.c
char			*get_path(char **envp, char *cmds);
char			*create_full_path(char *dir, char *cmds);

// get_env.c
char			*get_env(char **env, char *var_name);


// export.c
int				detect_export_call(t_minishell *ms, char **tokens);
void			export_handling(t_minishell *ms, int i);
int				count_en_var(char **env, int count);
void			set_env_var(t_minishell *ms, const char *var_name,
					const char *value);
void			print_env(char **env);
char			**realloc_env(char **env, int new_size);


// unset.c
int				detect_unset_call(t_minishell *ms, char **tokens);
void			unset_handling(t_minishell *ms, char **tokens, int i);
int				find_env_index(char **env, const char *var_name);
bool			remove_env_var1(t_minishell *ms, int idx);
void			free_ptr(void *ptr);
int				env_var_count(char **env);



// commands.c
int				call_commands(t_minishell *ms);
int				exec_builtin(t_minishell *ms, char **tokens, int is_child);
int				ft_execvp(char **tokens, char **envp);
int				exec_builtin2(t_minishell *ms, char **tokens, int is_child);

/* redirections*/

// exec_redirections.c
int				exec_redirections(t_minishell *ms);

// redirection.c
int				redirect(t_minishell *ms, int return_value, int k, int *i);
int				redirect_input(char *file);
int				redirect_output(char *file);
int				append_output(char *file);
int				redirect_heredoc(t_minishell *ms, int i);

// redirection_utils.c
int				count_tokens_left(t_minishell *ms);
void			recreate_tokens(t_minishell *ms, int tokens_count);

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

/* pipes */

// pipes.c
void			init_pipes(t_pipes *p);
int				**allocate_pipes(t_pipes *p);
void			close_pipes(t_pipes *p);
void			pipes_redirection(t_pipes *p);

// exec_pipes.c
int				exect_pipes(t_minishell *ms);
char			**extract_args(char **tokens, int start, int end);
void			handle_child_process(t_minishell *ms, t_pipes *p);
int				create_and_manage_process(t_minishell *ms, t_pipes *p,
					pid_t *pid);
int				call_commands_pipes(t_minishell *ms, t_pipes *p);

// pipes_redirections.c
int				exec_redirection_pipes(t_pipes *p, t_minishell *ms);
int				count_args_left(t_pipes *p);
void			recreate_pipes_args(t_pipes *p, int args_count);
int				redirect_pipes(t_minishell *ms, t_pipes *p, int return_value, int k, int *i);

// pipes_utils.c
void			print_arg_protected_array(t_pipes *p);
int				count_pipes(t_minishell *ms, char **str);
void			fill_pipes_protected_array(t_minishell *ms, t_pipes *p,
					int cmd_start);
t_bool			pipes_has_redirect(t_pipes *p);


#endif
