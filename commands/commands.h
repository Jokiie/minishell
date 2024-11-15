/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/14 12:28:58 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

// cd.c
int		cd(t_minishell *ms);
int		detect_cd_call(t_minishell *ms);

// pwd.c
int		pwd(t_minishell *ms);
int		detect_pwd_call(t_minishell *ms);

// echo.c
void	echo(t_minishell *ms, char **tokens, int opt);
int		detect_echo_call(t_minishell *ms);

// executable.c
int		detect_executable(t_minishell *ms);
int     check_error_executable(char *executable);

// env.c
int		detect_env_call(t_minishell *ms);
int		env(t_minishell *ms);

//exit.c
t_bool  is_exit(char *token);

// get_path.c
char	*get_path(char *cmds);
char	*create_full_path(char *dir, char *cmds);

// export.c
int		detect_export_call(t_minishell *ms, int k);
void	export_handling(t_minishell *ms, int i);
int		count_en_var(char **env, int count);
void	set_env_var(t_minishell *ms, const char *var_name, const char *value);

// unset.c
int		detect_unset_call(t_minishell *ms, int k);
void	unset_handling(t_minishell *ms, int i);
int		find_env_index(char **env, const char *var_name);
void	remove_env_var(char **env, int index);


// commands.c
int		call_commands(t_minishell *ms);
int		exec_builtin(t_minishell *ms);
int     ft_execvp(char **tokens, char **envp);

#endif