/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/10/18 02:46:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

// Commands
int		cd(t_minishell *ms, char **tokens);
int		detect_cd_call(t_minishell *ms, char **tokens);

int		pwd(t_minishell *ms, char **tokens);
int		detect_pwd_call(t_minishell *ms, char **tokens);

void	echo(char **tokens);
void	echo_n(char **tokens);
int		detect_echo_call(t_minishell *ms, char **tokens, int k);

int		detect_executable(t_minishell *ms, char **tokens, int k);

// ft_check_cmd_path.c
char	*create_full_path(char *dir, char *cmds);
char	*get_last_dir(char *cmds);
char	*find_executable_path(char *cmds);

// commands.c
int		parse_input(t_minishell *ms, char *input);
int		call_commands(t_minishell *ms);
int		exec_path_cmds(t_minishell *ms, char **tokens, int i);
int		external_cmds(t_minishell *ms);
int		built_in_cmds(t_minishell *ms);

int		check_error_cd(t_minishell *ms);
#endif