/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:22:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/12 02:14:15 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../includes/minishell.h"

// trimmer.c
void	trim_tokens(t_minishell *ms);
char	*ft_toktrim(t_minishell *ms, char *str, int len);

// characterizer.c
char	*characterizer(t_minishell *ms, char *token);
char	*var_extractor(char *token, int *i);
char	*insert_variable_value(char *before, char *var, char *after);
void	characterize_tokens(t_minishell *ms);

// tokenizer.c
int		separe_line(t_minishell *ms, char *line, int i, int k);
void	tokenizer(t_minishell *ms, char *line, int k);
int		ft_create_tokens(t_minishell *ms, char *line);
int		ft_quotes_detector(t_minishell *ms, char *str, int i);

#endif