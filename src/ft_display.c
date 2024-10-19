/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:29:34 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/19 12:37:06 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_arrow_color(t_minishell *ms, char *cwd_dup)
{
	char	*arrow_color;
	
	if (ms->ret == 0)
    {
		arrow_color = ft_strjoin(cwd_dup, GREEN " ➜  " RESET BOLDRESET);
    }
    else
	{
    	arrow_color = ft_strjoin(cwd_dup, RED " ➜  " RESET BOLDRESET);
    }
    return (arrow_color);
}

char	*get_user_color(char *username)
{
	char	*color;
	
	if (ft_strncmp(username, "ccodere", 7) == 0)
	{
    	color = ft_strjoin(MAGENTA BOLD "", username);
    }
    else if (ft_strnstr(username, "matis", ft_strlen(username)))
    {
		color = ft_strjoin(BLUE BOLD "", username);
    }
    else
    {
        color = ft_strjoin(CYAN BOLD "", username);
    }
    return (color);
}