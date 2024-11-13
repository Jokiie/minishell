/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/11/12 18:04:41 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

// cd.c
int		cd(t_minishell *ms, int k);
int		detect_cd_call(t_minishell *ms, int k);

// pwd.c
int		pwd(t_minishell *ms);
int		detect_pwd_call(t_minishell *ms, int k);

// echo.c
void	echo(char **tokens, int opt);
int		detect_echo_call(t_minishell *ms, int k);

// pecho.c
void	p_echo(char **tokens);
void	p_echo_n(char **tokens);
int		p_detect_echo_call(t_minishell *ms, int k);

// executable.c
int		detect_executable(t_minishell *ms, int k);

// env.c
int		detect_env_call(t_minishell *ms, int k);
int		env(t_minishell *ms, int k);

// unset.c
int	detect_unset_call(t_minishell *ms, int k);
void	unset_handling(t_minishell *ms, int i);
int	find_env_index(char **env, const char *var_name);
void	remove_env_var(char **env, int index);

// find_executable_path.c
char	*find_executable_path(char *cmds);
char	*create_full_path(char *dir, char *cmds);
char	*get_last_dir(char *cmds);

// commands.c
int		execute_input(t_minishell *ms, char *input);
int		call_commands(t_minishell *ms);
int		exec_path_cmds(t_minishell *ms, char **tokens, int k);
int     forked_builtin_cmds(t_minishell *ms);
int		built_in_cmds(t_minishell *ms);

#endif