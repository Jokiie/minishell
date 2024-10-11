/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/10/11 13:33:07 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../includes/minishell.h"

void	cd(char **tokens);
void	echo(char **tokens);
void	echo_n(char **tokens);
void	pwd(char **tokens);

char	*ft_create_full_path(char *dir, char *cmds);
char	*ft_get_last_dir(char *cmds);
char	*ft_create_n_check_path(char *cmds);

void	ft_call_commands(t_minishell *ms);
t_bool	ft_call_custom_cmds(t_minishell *ms);
t_bool	ft_exec_commands(t_minishell *ms, char **tokens);
t_bool	ft_custom_cmds(t_minishell *ms);

#endif