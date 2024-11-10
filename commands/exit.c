/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:09:45 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/10 00:11:55 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

t_bool  is_exit(char *line)
{
    if (ft_strncmp(line, "exit\0", 5) == 0)
        return (TRUE);
    return (FALSE); 
}
