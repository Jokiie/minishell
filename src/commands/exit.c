/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:09:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/21 03:45:57 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int detect_exit_call(t_minishell *ms, char **tokens, int is_child)
{
    int return_value;

    return_value = 0;
    if (ft_strncmp(tokens[0], "exit\0", 5) == 0)
    {    
        return_value = ft_exit(ms, tokens, is_child);
        return (return_value);
    }    
    return (CMD_NOT_FOUND); 
}

int   ft_exit(t_minishell *ms, char **tokens, int is_child)
{
    int return_code;

    return_code = 0;
    if (tokens[1] && tokens[2])
    {
        ft_fprintf(2, "ms: exit: too many arguments\n");
        return (ERROR);
    }
    if (tokens[1] && !contains_only_digits(tokens[1]))
    {
        ft_fprintf(2, "ms: exit: %s: numeric argument required\n", tokens[1]);
        return (SYNTAX_ERROR);
    }
    if (is_child == 1)
    {
        if (tokens[1])
            return_code = ft_atoi(tokens[1]);
        return (return_code);
    }
    else
    {
        if (tokens[1])
             return_code = ft_atoi(tokens[1]);
        exit_minishell(ms, return_code);
    }
    return (SUCCESS);
}
