/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:22:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 04:46:08 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../includes/minishell.h"

// tokens_creator.c
int		tokens_creator(t_minishell *ms, char *line);

// tokenizer.c
int		separe_line(t_minishell *ms, char *line, int i, int *k);
char	**tokenizer(t_minishell *ms, char *line);
char	*meta_chars_extractor(char *line, int *i);

// quotes_detector.c
int		ft_quotes_detector(t_minishell *ms, char *line, int i);
int		ft_open_quotes_checker(t_minishell *ms, char *line);

// characterizer.c
char	**characterizer(t_minishell *ms, char **tokens);
char	*characterize_token(t_minishell *ms, char *token, int i);
char	*apply_nbr_expansion(t_minishell *ms, char *token_dup, int i);

// var_expansion.c
char	*apply_var_expansion(char *token_dup, int i);
char	*insert_variable_value(char *before, char *var, char *after);
char	*var_extractor(char *token, int *i);

// nbr_expansion.c
char	*apply_nbr_value(char *token_dup, int i, int nbr);
char	*insert_nbr_value(char *before, char *after, int nbr);
char	*single_var_extractor(char *token, int *i);

// trimmer.c
char	**trimmer(t_minishell *ms, char **tokens);
char	*ft_toktrim(t_minishell *ms, char *token, int len);

// has_meta.c
t_bool	has_redirect(char **tokens);
t_bool	has_heredoc(char **tokens);
t_bool	has_pipe(char *input);

// is_meta.c
t_bool	is_pipe(char *token);
t_bool	is_heredoc(char *token);
t_bool	is_redirect(char *token);

// syntax_error.c
int		check_syntax(char **tokens);
int		errors_redirect(char **tokens);
int		error_pipes(char **tokens);

#endif