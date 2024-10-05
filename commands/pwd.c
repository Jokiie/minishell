/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:52:07 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 23:49:57 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Display the current working directory
*/
void    pwd(char **args)
{
    char cwd[BUFFER_SIZE];
    
    if (args[1] != NULL)
    {
        ft_fprintf(2, "pwd: too many arguments\n");
        return ;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_printf("%s\n", cwd);
    else
    {
        ft_fprintf(2, "getcwd() error"); 
        return ;
    }
}
