/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:50 by matislessar       #+#    #+#             */
/*   Updated: 2024/10/10 10:59:40 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../libft/libft.h"
#include "../includes/minishell.h"
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

void	cd(char **tokens);
void	echo(char **tokens);
void	echo_n(char **tokens);
char	*ft_create_full_path(char *dir, char *cmds);
char	*ft_get_last_dir(char *cmds);
char	*ft_create_n_check_path(char *cmds);
void	ft_call_commands(t_minishell *ms);
t_bool	ft_call_custom_cmds(t_minishell *ms);
t_bool	ft_exec_commands(t_minishell *ms, char **tokens);
t_bool	ft_custom_cmds(t_minishell *ms);



#endif