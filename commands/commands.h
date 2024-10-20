/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/10/20 13:28:48 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

// cd.c
int		cd(t_minishell *ms, int k);
int		detect_cd_call(t_minishell *ms, int k);

// pwd.c
int		pwd(t_minishell *ms, int k);
int		detect_pwd_call(t_minishell *ms, int k);

// echo.c
void	echo(char **tokens);
void	echo_n(char **tokens);
int		detect_echo_call(t_minishell *ms, int k);

// executable.c
int		detect_executable(t_minishell *ms, int k);

// env.c
int		detect_env_call(t_minishell *ms, int k);
int		env(t_minishell *ms, int k);

// find_executable_path.c
char	*find_executable_path(char *cmds);
char	*create_full_path(char *dir, char *cmds);
char	*get_last_dir(char *cmds);

// commands.c
int		parse_input(t_minishell *ms, char *input);
int		call_commands(t_minishell *ms);
int		exec_path_cmds(t_minishell *ms, char **tokens, int i);
int     external_builtin_cmds(t_minishell *ms);
int		built_in_cmds(t_minishell *ms);

#endif