/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/13 13:30:21 by ccodere          ###   ########.fr       */
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
void	echo(char **tokens, int opt);
void	echo_n(char **tokens);
int		detect_echo_call(t_minishell *ms);

// pecho.c
void	p_echo(char **tokens);
void	p_echo_n(char **tokens);
int		p_detect_echo_call(t_minishell *ms, int k);

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

// commands.c
int		call_commands(t_minishell *ms);
int		ft_execvp(char **tokens, char **envp);
int		exec_builtin(t_minishell *ms);

#endif