/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:22:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 11:55:21 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../includes/minishell.h"

// trimmer.c
char	**trimmer(t_minishell *ms, char **tokens);
char	*ft_toktrim(t_minishell *ms, char *token, int len);

// characterizer.c
char    **characterizer(t_minishell *ms, char **tokens);
char	*characterize_token(t_minishell *ms, char *token);
char	*var_extractor(char *token, int *i);
char	*insert_variable_value(char *before, char *var, char *after);

// tokenizer.c
int		separe_line(t_minishell *ms, char *line, int i, int k);
char	**tokenizer(t_minishell *ms, char *line);
int		ft_create_tokens(t_minishell *ms, char *line);
int		ft_quotes_detector(t_minishell *ms, char *line, int i);

#endif