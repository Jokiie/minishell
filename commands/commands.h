/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/10/13 22:22:17 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

// Commands
void	cd(char **tokens);

void	pwd(char **tokens);
int	    detect_pwd_call(char **tokens);

void	echo(char **tokens);
void	echo_n(char **tokens);
int		detect_echo_call(char **tokens, int i);

int     detect_executable(t_minishell *ms, char **tokens, int k);

// ft_check_cmd_path.c
char	*ft_create_full_path(char *dir, char *cmds);
char	*ft_get_last_dir(char *cmds);
char	*ft_create_n_check_path(char *cmds);

// commands.c
void	ft_call_commands(t_minishell *ms);
int		ft_exec_commands(t_minishell *ms, char **tokens, int i);
int		ft_call_custom_cmds(t_minishell *ms);
int		ft_custom_cmds(t_minishell *ms);

#endif