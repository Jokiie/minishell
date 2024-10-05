/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:08:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/05 02:03:26 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define SUCCESS 1
# define FAIL 0
# define ERROR -1

# define SURL "\e[7m"
# define SURLRESET "\e[0m"

# define BOLD "\033[1m"
# define BOLDRESET "\033[0m"

typedef struct s_token
{
	char	start;
	char	end;
	t_bool	in_dquotes;
	t_bool	in_squotes;
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
	char	**args;
	size_t	argc;
	int		std_in;
	int		std_out;
	int		std_err;
	t_token token;
}			t_minishell;

// commands.c
void	cd(char **args);
void    pwd(char **args);

// ft_if_is.c
int			ft_is_dquote(int c);
int			ft_is_squote(int c);
int			ft_isquotes(int c);
int			ft_isredirect(int c);
int			ft_isnull(int c);

// ft_commands.c
void		ft_call_commands(char **args, char **envp);
int			ft_exec_commands(char **args, char **envp);
int			ft_call_custom_cmds(char **args, char **envp);
int			ft_custom_cmds(char **args, char **envp);

// ft_check_cmd_path.c
char		*ft_create_full_path(char *dir, char *cmds);
char		*ft_get_last_dir(char *cmds);
char		*ft_create_n_check_path(char *cmds);

// ft_parser.c
void		ft_init_token(t_minishell *ms, char *line, int i, int k);

// ft_utils.c
void		ft_free_split(char **args);
int			ft_count_args(char **args);
int			ft_charcount(char *line, char to_count);
char		*ft_strpass(char *str, int to_pass, int len);
// ft_exit.c
void		ft_exit_minishell(t_minishell *ms);
void		ft_free_vars(t_minishell *ms);

// redirection.c
int			ft_isredirect(int c);
void		redirect_input(char *file);

#endif