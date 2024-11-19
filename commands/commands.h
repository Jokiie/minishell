/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/19 00:53:48 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

// cd.c
int		cd(char **tokens);
int		detect_cd_call(char **tokens);

// pwd.c
int		pwd(t_minishell *ms);
int		detect_pwd_call(t_minishell *ms, char **tokens);

// echo.c
void	echo(t_minishell *ms, char **tokens, int opt);
int		detect_echo_call(t_minishell *ms, char **tokens);

// executable.c
int		detect_executable(t_minishell *ms, char **tokens);
int     check_error_executable(char *executable);

// env.c
int		detect_env_call(t_minishell *ms, char **tokens);
int		env(t_minishell *ms, char **tokens);

//exit.c
int     detect_exit_call(t_minishell *ms, char **tokens,  int is_child);
int  	ft_exit(t_minishell *ms, char **tokens, int is_child);

// get_path.c
char	*get_path(char *cmds);
char	*create_full_path(char *dir, char *cmds);

// export.c
int		detect_export_call(t_minishell *ms);
void	export_handling(t_minishell *ms, int i);
int		count_en_var(char **env, int count);
void	set_env_var(t_minishell *ms, const char *var_name, const char *value);

// unset.c
int		detect_unset_call(t_minishell *ms);
void	unset_handling(t_minishell *ms, int i);
int		find_env_index(char **env, const char *var_name);
void	remove_env_var(char **env, int index);


// commands.c
int		call_commands(t_minishell *ms);
int		exec_builtin(t_minishell *ms, char **tokens, int is_child);
int     ft_execvp(char **tokens, char **envp);

#endif