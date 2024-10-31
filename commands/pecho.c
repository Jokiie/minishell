/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pecho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:35:18 by matislessar       #+#    #+#             */
/*   Updated: 2024/10/28 14:53:54 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*	
	call echo but this currently while it should not : hello echo hello 
	Do not work with redirection either, because redirection is currently
   	called in the fork, in commands.c, which is executed if the custom
	commands failed...
*/
int	p_detect_echo_call(t_minishell *ms, int i)
{
	if (((i == 0) && ft_strncmp(ms->tokens[i], "pecho\0", 6) == 0
			&& ft_strncmp(ms->tokens[i + 1], "-n\0", 3) == 0))
	{
		echo_n(ms->tokens);
		ms->ret = SUCCESS;
	}
	else if ((i == 0) && ft_strncmp(ms->tokens[i], "pecho\0", 6) == 0)
	{
		echo(ms->tokens);
		ms->ret = SUCCESS;
	}
	return (ms->ret);
}

/* Print the tokens after echo */
void	p_echo(char **tokens)
{
	int	k;

	k = 1;
	while (tokens[k + 1])
	{
		ft_printf("%s ", tokens[k]);
		k++;
	}
	ft_printf("%s\n", tokens[k]);
}

/* Print the tokens after echo -n */
void	p_echo_n(char **tokens)
{
	int	k;

	k = 2;
	while (tokens[k + 1])
	{
		ft_printf("%s ", tokens[k]);
		k++;
	}
	ft_printf("%s", tokens[k]);
	ft_printf(SURL "%%\n" SURLRESET);
}