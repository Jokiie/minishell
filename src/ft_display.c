/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:29:34 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/19 13:21:01 by ccodere          ###   ########.fr       */
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

char	*get_user_color(t_minishell *ms, char *username)
{
	char	*color;
	
	if (ft_strncmp(ms->user, "ccodere", 7) == 0)
	{
        ms->user = "Celia";
    	color = ft_strjoin(MAGENTA BOLD "", ms->user);
    }
    else if (ft_strnstr(username, "matis", ft_strlen(username)))
    {
        ms->user = "Matis";
		color = ft_strjoin(BLUE BOLD "", ms->user);
    }
    else if (!username || !ms->user)
    {
        ms->user = "Human";
        color = ft_strjoin(YELLOW BOLD "", ms->user);
    }
    else
    {
        color = ft_strjoin(CYAN BOLD "", ms->user);
    }
    return (color);
}
