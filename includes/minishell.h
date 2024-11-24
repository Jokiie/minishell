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

# define MAX_ARGS 10000
# define SIZE_CHAR_PTR sizeof(char *)

# define MAX_PATH 4096
# define MAX_HEREDOC 1024

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
	char		**fd_name;
	char		*delim;
	char		*input;
	char		*line;
	int			count;
	int			index;
	t_bool		in_quotes;
}				t_heredoc;

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
	char		*input;
	char		*prompt_name;
	char		*user;
	char		*cwd;
	char		*prev_cwd;
	char		**history;
	char		**env;
	char		**tokens;
	char		**pretokens;
	char		**characterized;
	int			tokc;
	int			ret;
	char		*path;
	t_token		token;
	t_heredoc	heredoc;
	t_bool		interactive;
	t_bool		in_pipe;
	t_pipes		p;
}				t_minishell;

// minishell.c

void			init_heredoc_data(t_minishell *ms);

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
void			print_tokens(char **tokens);
char			**ft_envdup(char **envp);
int				wait_children(void);

// exit_minishell.c
void			exit_minishell(t_minishell *ms, int return_code);
void			exit_child(t_minishell *ms, int return_code, t_bool in_pipe);

// free.c
void			free_data(t_minishell *ms);
void			ft_free(void *ptr);
void			free_at_address(char **str);
void			free_at_exit(t_minishell *ms);
void			free_int_array(int **arr);

// free_array_tab.c
void			free_tokens_address(char ***tokens);
void			free_tokens(char **tokens);

// free_protected_array.c
void			free_protected_array(int **array);

// error.c
int				check_error(char *cmd);

// prompt_name.c
char			*get_prompt_name(t_minishell *ms);
char			*get_user_color(t_minishell *ms);
char			*get_arrow_color(t_minishell *ms, char *cwd_dup);
char			**get_cwdsplit(t_minishell *ms);

/* debug */

// debug.c
void			print_debug(char **tokens);
void			print_protected_array(char **tokens, int **protected);

/* Tokenization */

// tokens_creator.c
int				tokens_creator(t_minishell *ms, char *line);
char			**transformer(t_minishell *ms);
void			fill_protected_arr(t_minishell *ms, char **tokens);

// tokenizer.c
int				separe_line(t_minishell *ms, char *line, int i, int *k);
char			**tokenizer(t_minishell *ms, char *line);
char			*meta_chars_extractor(char *line, int *i);
int				count_words(char const *line);

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

// cleaner.c

char			**cleaner(char **tokens);
t_bool    		has_empty_token(char **tokens);
int				count_valid_tokens(char **tokens);

// has_meta.c
t_bool			has_redirect(t_minishell *ms, char **tokens);
t_bool			has_type(char **tokens, int **protected,
					t_bool (*is_type)(char *));
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
t_bool			is_redirect_output(char *token);
t_bool			is_type(char *token, t_bool (*is_type)(char *));
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

// count.c

int				count_type(char **tokens, int **protected,
					t_bool (*is_type)(char *));
int				count_tokens(char **tokens);

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
t_bool  		is_valid_arg(char *token);

// get_path.c
char			*get_path(char **envp, char *cmds);
char			*create_full_path(char *dir, char *cmds);

// get_env.c
char			*get_env(char **env, char *var_name);

// export.c
int				detect_export_call(t_minishell *ms, char **tokens);
void			export_handling(t_minishell *ms, char **tokens, int i);
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
void			handle_one_child_process(t_minishell *ms);
int				ft_execvp(char **tokens, char **envp);
int				exec_builtin(t_minishell *ms, char **tokens, int is_child);
int				exec_builtin2(t_minishell *ms, char **tokens, int is_child);

/* redirections*/

// exec_redirections.c
int				exec_redirections(t_minishell *ms, char **tokens,
					int **protected, t_bool in_pipe);
int				redirect(char *tokens, char *file);
int				redirect_heredocs(t_minishell *ms);

// redirection.c
int				redirect_input(char *file);
int				redirect_output(char *file);
int				append_output(char *file);
int				redirect_heredoc(char *file);

// redirection_utils.c
char			**recreate_tokens(char **tokens, int **protected, int count,
					t_bool in_pipe);
int				get_filtered_tokc(char **tokens, int **protected);
int				cat_heredoc(char *file);

// heredoc.c
int				process_heredocs(t_minishell *ms);
int				heredoc(t_minishell *ms);
int				fill_heredoc(t_minishell *ms, int fd);
char			*create_heredoc_name(t_minishell *ms);

// heredoc_expander.c
char			*expand_line(t_minishell *ms, char *line);
char			*expander(t_minishell *ms, char *line);

// heredoc_utils.c
void			check_quotes_delim(t_minishell *ms, int index);
t_bool			line_is_null(char *line, char *delim);
t_bool			is_delim(char *line, char *delim);
t_bool			break_check(char *line, char *delim);
char			*trim_delim(t_minishell *ms, char *delim);
void			free_tmp_data(t_minishell *ms);

// heredoc_reset.c
void			unlink_heredocs(t_minishell *ms);
void			reset_heredoc(t_minishell *ms);
void			clear_heredoc_names(t_minishell *ms);

// heredoc_statics.c
void			reset_heredoc_statics(void);
int				update_heredoc_index(t_bool reset);
int				update_heredoc_number(t_bool reset);
int				update_heredoc_count(t_bool reset);

/* pipes */

// pipes.c
void			init_exec_pipes(t_minishell *ms, int *i);
void			init_pipes(t_minishell *ms);
int				**allocate_pipes(t_minishell *ms);
void			close_pipes(t_minishell *ms);
int				pipes_redirection(t_minishell *ms);

// exec_pipes.c
int				exect_pipes(t_minishell *ms);
void			handle_pipe_cmd(t_minishell *ms, int i, pid_t *pid);
void			handle_child_process(t_minishell *ms);
int				create_and_manage_process(t_minishell *ms, pid_t *pid);
int				call_commands_pipes(t_minishell *ms);

// pipes_redirections.c
int				exec_redirection_pipes(t_pipes *p, t_minishell *ms);
int				count_args_left(t_pipes *p);
void			recreate_pipes_args(t_pipes *p, int args_count);
int				redirect_pipes(t_minishell *ms, t_pipes *p, int return_value, int k, int *i);

// pipes_utils.c
void			fill_pipes_protected_array(t_minishell *ms, int cmd_start);
char			**extract_args(char **tokens, int start, int end);
void			handle_last_cmd(t_minishell *ms, int *i);
#endif
