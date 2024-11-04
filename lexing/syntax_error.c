/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 03:19:33 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/04 04:47:35 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int check_syntax(char **tokens)
{
    if (error_pipes(tokens) != SUCCESS || errors_redirect(tokens) != SUCCESS)
        return (SYNTAX_ERROR);
    return (SUCCESS);
}

int error_pipes(char **tokens)
{
    int k;

    k = 0;
    while (tokens[k])
    {
        if (is_pipe(tokens[k]))
        {
            if (tokens[k + 1] == NULL)
            {
                ft_fprintf(2, "ms: syntax error near unexpected token '|'\n");
                return (SYNTAX_ERROR);
            }
            else if (is_pipe(tokens[k + 1]))
            {
                ft_fprintf(2, "ms: syntax error near unexpected token '||'\n");
                return (SYNTAX_ERROR);
            }
            else if (is_redirect(tokens[k + 1]) || is_heredoc(tokens[k + 1]))
            {
                ft_fprintf(2, "ms: syntax error near unexpected token '|'\n");
                return (SYNTAX_ERROR);
            }
        }
        k++;
    }
    return (SUCCESS);
}

int errors_redirect(char **tokens)
{
    int k;

    k = 0;
    while (tokens[k])
    {
        if (is_redirect(tokens[k]) || is_heredoc(tokens[k]))
        { 
            if (tokens[k + 1] == NULL)
            {
                ft_fprintf(2, "ms: syntax error near unexpected token 'newline'\n");
                return (SYNTAX_ERROR);
            }
            else if (is_pipe(tokens[k + 1]) || is_redirect(tokens[k + 1])
                || is_heredoc(tokens[k + 1]))
            {
                ft_fprintf(2, "ms: syntax error near unexpected token '%s'\n", tokens[k + 1]);
                return (SYNTAX_ERROR);
            }
        }
        k++;
    }
    return (SUCCESS);
}