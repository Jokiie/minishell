/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:08:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/10 02:26:06 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <sys/wait.h>
# include "readline/readline.h"
# include "readline/history.h"


# define SUCCESS 0
# define FAIL 1
# define ERROR -1

# define SURL "\e[7m"
# define SURLRESET "\e[0m"

# define BOLD "\033[1m"
# define BOLDRESET "\033[0m"

#define MB_SIZE 2097152
#define PTR_SIZE sizeof(char *)

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
	char	**env;
	char	**tokens;
	char	**pretokens;
	size_t	tokc;
	int		std_in;
	int		std_out;
	int		std_err;
	t_token	token;
}			t_minishell;

// commands.c
void		cd(char **tokens);
void		pwd(char **tokens);
void		echo(char **tokens);
void		echo_n(char **tokens);

// ft_if_is.c
int			ft_is_dquote(int c);
int			ft_is_squote(int c);
int			ft_isquotes(int c);
int			ft_isredirect(int c);

// ft_commands.c
void		ft_call_commands(t_minishell *ms);
t_bool		ft_exec_commands(t_minishell *ms, char **tokens);
t_bool		ft_call_custom_cmds(t_minishell *ms);
t_bool		ft_custom_cmds(t_minishell *ms);

// ft_check_cmd_path.c
char		*ft_create_full_path(char *dir, char *cmds);
char		*ft_get_last_dir(char *cmds);
char		*ft_create_n_check_path(char *cmds);

// ft_init_tokens.c
int			ft_create_tokens(t_minishell *ms, char *line);
char		*characterizer(t_minishell *ms, char *token);
void		characterize_tokens(t_minishell *ms);

// ft_utils.c
void		ft_free_tokens(char **tokens);
int			ft_count_tokens(char **tokens);
int			ft_charcount(char *line, char to_count);
char		*ft_strpass(char *str, int to_pass, int len);
char		*ft_strskip(char *str, char *to_pass, int len);

// ft_exit.c
void		ft_exit_minishell(t_minishell *ms);
void		ft_free_vars(t_minishell *ms);

// redirection.c
void		ft_exec_redirection(t_minishell *ms);
void		ft_recreate_tokens(t_minishell *ms, int i);
void		redirect_input(t_minishell *ms, char *file);
void		redirect_output(t_minishell *ms, char *file);
#endif