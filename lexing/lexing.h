/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:22:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/14 00:06:42 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../includes/minishell.h"

void	redirect_input(t_minishell *ms, char *file);
void	redirect_output(t_minishell *ms, char *file);
void	ft_recreate_tokens(t_minishell *ms, int i);
void	ft_exec_redirection(t_minishell *ms);

char	*apply_var_expansion(char *token_dup, int i);

// trimmer.c
char	**trimmer(t_minishell *ms, char **tokens);
char	*ft_toktrim(t_minishell *ms, char *token, int len);

// characterizer.c
char	**characterizer(t_minishell *ms, char **tokens);
char	*characterize_token(t_minishell *ms, char *token, int i);
char	*var_extractor(char *token, int *i);
char	*insert_variable_value(char *before, char *var, char *after);

// tokenizer.c
int		separe_line(t_minishell *ms, char *line, int i, int k);
char	**tokenizer(t_minishell *ms, char *line);
int		ft_create_tokens(t_minishell *ms, char *line);
int		ft_quotes_detector(t_minishell *ms, char *line, int i);

#endif