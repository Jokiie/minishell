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
# define CATCH_ALL 255

# define SURL "\001\e[7m\002"
# define SURLRESET "\001\e[0m\002"

# define BOLD "\001\033[1m\002"
# define BOLDRESET "\001\033[0m\002"

# define MAX_PATH 4096
# define SIZE_BUF 1024
# define MAX_META 256

# define SQUOTE 1
# define DQUOTE 2
# define EXPANSION 3
# define DQUOTE_EXP 4

typedef struct s_counter
{
	int				i;
	size_t			j;
	size_t			g;
	int				k;
}					t_counter;

typedef struct s_token
{
	int				start;
	int				end;
	int				size;
	int				*quoted;
	int				*expanded;
	int				**state_array;
	size_t			state_array_capacity;
	size_t			state_array_size;
	int				**new_state_array;
	size_t			new_state_array_capacity;
	size_t			new_state_array_size;
	size_t			state_index;
	int				expansion_state;
	int				quoted_state;
	size_t			expansion_start;
	size_t			expansion_end;
	size_t			expansion_len;
	char			**db_buffer;
	size_t			db_size;
	size_t			db_capacity;

	int				*new_quoted;

	t_bool			is_meta;
	t_bool			in_dquotes;
	t_bool			in_squotes;
}					t_token;

typedef struct s_heredoc
{
	char			**fd_name;
	char			*delim;
	char			*input;
	char			*line;
	int				count;
	int				index;
	t_bool			in_quotes;
}					t_heredoc;

typedef struct s_pipes
{
	char			**p_args;
	int				**pipes;
	int				num_pipes;
	int				cmd_num;
	int				cmd_start;
	t_bool			last_cmd;
	int				ret;
	int				*arg_quoted;
	int				*arg_expanded;
}					t_pipes;

typedef struct s_minishell
{
	char			*input;
	char			*prompt_name;
	char			*user;
	char			*cwd;
	char			*prev_cwd;
	char			**history;
	char			**env;
	char			**tokens;
	char			**pretokens;
	char			**expanded;
	int				tokc;
	int				ret;
	char			*path;
	t_token			token;
	t_heredoc		heredoc;
	t_bool			in_pipe;
	t_pipes			p;
	pid_t			pid;
	sig_atomic_t	received_sig;
}					t_minishell;

// minishell.c

void				init_heredoc_data(t_minishell *ms);

// signal_handler.c
void				init_signals_interactive(t_minishell *ms);
void				init_signals_interactive_heredocs(t_minishell *ms);
void				handle_sigint(int sig);
void				sync_signals(t_minishell *ms);
void				handle_sigint_hd(int sig);

// utils.c
void				print_tokens(char **tokens);
char				**ft_envdup(char **envp);
int					wait_children(t_minishell *ms);
void				welcome(t_minishell *ms);

// exit_minishell.c
void				exit_minishell(t_minishell *ms, int return_code);
void				exit_child(t_minishell *ms, int return_code,
						t_bool in_pipe);

// free.c
void				free_data(t_minishell *ms);
void				free_at_exit(t_minishell *ms);
void				free_ptr(void *ptr);
void				free_at_address(char **str);
void				free_int_array(int **arr);

// free_array_tab.c
void				free_tokens_address(char ***tokens);
void				free_tokens(char **tokens);
void				free_state_array(t_minishell *ms, int count);

// free_protected_array.c ????
void				free_protected_array(int **array);

// error.c
int					check_error(char *cmd);
int					check_eacces(char *cmd);
int					check_enoent(char *cmd);
void				error_msg(char *cmd, char *msg);

// prompt_name.c
char				*get_prompt_name(t_minishell *ms);
char				**get_cwdsplit(t_minishell *ms);
char				*get_arrow_color(t_minishell *ms, char *cwd_dup);
char				*get_user_color(t_minishell *ms);

// debug.c
void				print_debug(char **tokens);
void				print_int_array(char **tokens, int **quoted);
void				print_expanded_array(char **tokens, int **expanded);
void				print_state_array(t_minishell *ms, char **tokens,
						int token_count);

/* Tokenization */

// tokens_creator.c
int					tokens_creator(t_minishell *ms, char *line);
char				**transformer(t_minishell *ms);

// tokens_creator_utils.c
void				init_counter(t_counter *c);
t_bool				is_expandable(t_minishell *ms, char *token, int k);
t_bool				need_to_be_expand(t_minishell *ms, char **tokens);
t_bool				is_space_or_meta2(t_minishell *ms, char *token, int *i,
						int k);

// tokenizer.c
int					separe_line(t_minishell *ms, char *line, int i, int *k);
t_bool				is_space_or_meta(t_minishell *ms, char *token, int *i);
char				**tokenizer(t_minishell *ms, char *line);
char				*meta_chars_extractor(char *line, int *i);
int					count_words(char const *line);

// quotes_detector.c
int					quotes_detector(t_minishell *ms, char *line, int i);
int					open_quotes_checker(t_minishell *ms, char *line);
int					quotes_detector2(t_minishell *ms, char *tok, int k, int i);
int					quotes_detector3(t_minishell *ms, char *token, int i,
						int k);

// parser.c
char				**parser(t_minishell *ms, char **tokens);
void				fill_state_array(t_minishell *ms, char *token, int k);
int					parse_squotes(t_minishell *ms, char *token, int i, int k);
int					parse_dquotes(t_minishell *ms, char *token, int i, int k);
int					update_state_array(t_minishell *ms, char **tokens);

// expander.
char				**expander(t_minishell *ms, char **tokens);
char				*expand_token(t_minishell *ms, char *token, int k);
char				*process_expansion(t_minishell *ms, char *dup, int *i,
						int k);
void				fill_expanded_buffer(t_minishell *ms, t_counter *c,
						char **expanded, char **tokens);
// expander_utils.c
t_bool				in_expandable_zone(t_minishell *ms, char *token, int i,
						int k);
t_bool				is_heredoc_delim(t_minishell *ms, char **tokens, int k);
t_bool				is_return_code_expansion(char *token, int i);
t_bool				is_variable_expansion(char *token, int i);

// var_expansion.c
char				*apply_var_expansion(t_minishell *ms, char *token_dup,
						int *i, int k);
char				*insert_variable_value(char *before, char *var,
						char *after);
char				*var_extractor(t_minishell *ms, char *token, int *i);

// nbr_expansion.c
char				*can_apply_nbr_expansion(t_minishell *ms, char *token_dup,
						int *i, int k);
char				*apply_nbr_expansion(t_minishell *ms, char *token_dup,
						int *i, int k);
char				*insert_nbr_value(char *before, char *nbr, char *after);
char				*single_var_extractor(char *token, int *i);

// retokenizer.c
char				**retokenizer(t_minishell *ms, char **tokens);
int					separe_token(t_minishell *ms, char *token, int *i, int k);
void				handle_non_empty(t_minishell *ms, char **tokens, int j);
void				fill_dbuffer(t_minishell *ms, t_counter *c, char **tokens,
						int saved_expanded);
void				extract_new_token(t_minishell *ms, char *token, int *i,
						int k);

// trimmer.c
char				**trimmer(t_minishell *ms, char **tokens);
char				*ft_toktrim(t_minishell *ms, char **tokens, int **tmp,
						int k);

// cleaner.c
char				**cleaner(t_minishell *ms, char **tokens);
int					count_valid_tokens(t_minishell *ms, char **tokens);

// int_arrays.c
void				init_int_arrays(t_minishell *ms, char **tokens);
void				init_quoted_array(t_minishell *ms, char **tokens);
void				init_expanded_array(t_minishell *ms, char **tokens);
void				update_arrays(t_minishell *ms);
void				update_quoted_array(t_minishell *ms, char **tokens);

// dynamic_buffer.c

char				**init_dbuffer(t_minishell *ms, size_t initial_capacity);
int					append_to_dbuffer_char(t_minishell *ms, char *data);
void				free_dbuffer(t_minishell *ms);

// state_array_utils.c
int					get_expanded_state(t_minishell *ms, char **tokens, int k);
int					get_quoted_state(t_minishell *ms, int start, int len,
						int k);
void				fill_new_state_array(t_minishell *ms, int end, int k);
void				fill_3_new_state_array(t_minishell *ms, int start, int len,
						int k);

// dynamic_buffer_int.c

int					*init_token_state_array(t_minishell *ms,
						size_t initial_capacity, int k);
int					add_to_state_array(t_minishell *ms, int data, int k);

int					*init_new_quoted(t_minishell *ms, size_t initial_capacity);
int					append_to_new_quoted(t_minishell *ms, int data);

int					*init_new_state_array(t_minishell *ms,
						size_t initial_capacity, int k);
int					add_to_new_state_array(t_minishell *ms, int data, int k);

// is.c
int					ft_is_dquote(int c);
int					ft_is_squote(int c);
int					ft_is_quotes(int c);
int					ft_ismeta_chars(int c);

// is_state.c
t_bool				is_squoted_char(t_minishell *ms, int *i, int k);
t_bool				is_quoted_char(t_minishell *ms, int *i, int k);
t_bool				is_expanded_char(t_minishell *ms, int *i, int k);

// has_meta.c
t_bool				has_type(char **tokens, int **quoted, int **expanded,
						t_bool (*is_type)(char *));
t_bool				has_redirects(char **tokens, int **quoted, int **expanded);
t_bool				has_quotes(char *token);

// is_meta.c
t_bool				is_redirect(char *token);
t_bool				is_type(char *token, t_bool (*is_type)(char *));
t_bool				is_meta(char *token);

// is_one_meta.c
t_bool				is_redirect_in(char *token);
t_bool				is_redirect_out(char *token);
t_bool				is_append(char *token);
t_bool				is_heredoc(char *token);
t_bool				is_pipe(char *token);

// syntax_error.c
int					check_syntax(t_minishell *ms);
int					errors_redirect(t_minishell *ms);
int					error_pipes(t_minishell *ms);

// contains_only.c
t_bool				contains_only_digits(char *line);
t_bool				contains_only_spaces(char *line);
t_bool				contains_only_type(char **tokens, int **protected,
						t_bool (*is_type)(char *));
t_bool				contains_only_quotes(char *token);
t_bool				contains_only_quotes2(t_minishell *ms, char **tokens,
						int k);

// count.c
int					count_type(char **tokens, int **quoted, int **expanded,
						t_bool (*is_type)(char *));
int					count_tokens(char **tokens);
int					count_size(char **tokens);

/* /commands */

// cd.c
int					detect_cd_call(t_minishell *ms, char **tokens);
int					cd(t_minishell *ms, char **tokens);
int					go_home(t_minishell *ms);
void				update_working_directories(t_minishell *ms);
int					change_directory(t_minishell *ms, const char *path);
int					go_old_pwd(t_minishell *ms);

// pwd.c
int					pwd(t_minishell *ms);
int					detect_pwd_call(t_minishell *ms, char **tokens);

// echo.c
void				echo(t_minishell *ms, char **tokens, int opt);
int					detect_echo_call(t_minishell *ms, char **tokens);
t_bool				valid_echo_arg(char *token);
int					update_echo_index(char **tokens, int *k);

// executable.c
int					detect_executable(t_minishell *ms, char **tokens);
int					check_error_executable(char *cmd);

// env.c
int					detect_env_call(t_minishell *ms, char **tokens);
int					env(t_minishell *ms, char **tokens);

// exit.c
int					ft_exit(t_minishell *ms, char **tokens, int is_child);
t_bool				is_valid_arg(char *token);
int					handle_valid_exit(t_minishell *ms, char **tokens,
						int is_child);
// exit_utils.c
t_bool				is_valid_size(char *token);
t_bool				iter_long_min(char *token);
t_bool				iter_long_max(char *token);

// get_path.c
char				*get_path(char **envp, char *cmds);
char				*create_full_path(char *dir, char *cmds);

// get_env.c
char				*get_env(char **env, char *var_name);

// export.c
int					detect_export_call(t_minishell *ms, char **tokens);
void				export_handling(t_minishell *ms, char **tokens, int i);
int					env_var_count(char **env);
void				set_env_var(t_minishell *ms, const char *var_name,
						const char *value);
void				export_declare_x(char **env);

// export_utils.c
char				**realloc_env(char **env, int new_size);
int					is_valid_var_name(const char *var_name);
char				*extract_var_name(const char *str);
char				*extract_var_value(const char *str, int j);
void				export_handling_x(t_minishell *ms, char **tokens, int i);

// unset.c
int					detect_unset_call(t_minishell *ms, char **tokens);
void				unset_handling(t_minishell *ms, char **tokens, int i);
int					find_env_index(char **env, const char *var_name);
char				**realloc_env_vars(t_minishell *ms, int size);
bool				remove_env_var1(t_minishell *ms, int idx);

// commands.c
int					call_commands(t_minishell *ms);
void				handle_child(t_minishell *ms);
int					ft_execvp(char **tokens, char **envp);
int					exec_builtin(t_minishell *ms, char **tokens);

/* redirections*/

// exec_redirections.c
int					exec_redirections(t_minishell *ms, char **tok, int **quoted,
						int **expanded);
int					redirect(char *tokens, char *file);

// redirection.c
int					redirect_input(char *file);
int					redirect_output(char *file);
int					append_output(char *file);
int					redirect_heredocs(t_minishell *ms);

// redirection_utils.c
void				remake_tokens(t_minishell *ms, char **tok, int **quoted,
						int **expanded);
char				**recreate_tokens(char **tok, int **quoted, int **expanded,
						int count);
int					get_filtered_tokc(char **tokens, int **quoted,
						int **expanded);

// heredoc.c
int					process_heredocs(t_minishell *ms);
int					heredoc(t_minishell *ms);
int					fill_heredoc(t_minishell *ms, int fd);

// heredoc_expander.c
char				*expand_line(t_minishell *ms, char *line, char *delim);
char				*heredoc_expander(t_minishell *ms, char *line, char *delim);
t_bool				is_same_size(char *str1, char *str2);

// heredoc_var_expansion.c
char				*apply_var_expansion_hd(t_minishell *ms, char *token_dup,
						int *i);
char				*var_extractor_hd(char *token, int *i);
char				*insert_variable_value_hd(t_minishell *ms, char *before,
						char *var, char *after);
// heredoc_nbr_expansion.c
char				*apply_nbr_expansion_hd(t_minishell *ms, char *token_dup,
						int *i);
char				*apply_nbr_value_hd(char *token_dup, int *i, int nbr);
char				*single_var_extractor_hd(char *token, int *i);
char				*insert_nbr_value_hd(char *before, char *after, int nbr);

// heredoc_utils.c
char				*create_heredoc_name(t_minishell *ms);
void				check_quotes_delim(t_minishell *ms, int index);
t_bool				break_check(char *line, char *delim);
t_bool				line_is_null(char *line, char *delim);
t_bool				is_delim(char *line, char *delim);

// heredoc_reset.c
void				unlink_heredocs(t_minishell *ms);
void				reset_heredoc(t_minishell *ms);
void				clear_heredoc_names(t_minishell *ms);
void				free_tmp_data(t_minishell *ms);
int					init_heredoc_names(t_minishell *ms);

// heredoc_statics.c
void				reset_heredoc_statics(void);
int					update_heredoc_index(t_bool reset);
int					update_heredoc_number(t_bool reset);
int					update_heredoc_count(t_bool reset);

// heredoc_signal.c
void				put_newline(int sig);
void				init_signals_noninteractive(void);

/* pipes */

// pipes.c
void				init_exec_pipes(t_minishell *ms, int *i);
void				init_pipes(t_minishell *ms);
int					**allocate_pipes(t_minishell *ms);
void				close_pipes(t_minishell *ms);
int					pipes_redirection(t_minishell *ms);

// exec_pipes.c
int					exect_pipes(t_minishell *ms);
void				handle_pipe_cmd(t_minishell *ms, int i, pid_t *pid);
void				handle_child_process(t_minishell *ms);
int					create_and_manage_process(t_minishell *ms, pid_t *pid);
int					call_commands_pipes(t_minishell *ms);

// pipes_redirections.c
int					exec_redirection_pipes(t_pipes *p, t_minishell *ms);
int					count_args_left(t_pipes *p);
void				recreate_pipes_args(t_pipes *p, int args_count);
int					redirect_pipes(t_minishell *ms, t_pipes *p,
						int return_value, int k, int *i);

// pipes_utils.c
void				fill_pipes_quoted_arr(t_minishell *ms, int cmd_start);
void				fill_pipes_expanded_arr(t_minishell *ms, int i);
char				**extract_args(t_minishell *ms, char **tokens, int start,
						int end);
void				handle_last_cmd(t_minishell *ms, int *i);
#endif
