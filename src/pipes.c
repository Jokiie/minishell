// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipes.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/09 13:13:36 by matislessar       #+#    #+#             */
// /*   Updated: 2024/10/09 16:15:45 by matislessar      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/minishell.h"

/*Recreate tokens for the pipes characters*/

void	ft_pipe_token(t_minishell *ms, int	i)
{
	int	k;
	char	**new_tokens;
	
	k = 0;
	new_tokens = (char **)malloc(sizeof(char *) * (i + 1));
	if (new_tokens)
		exit(-1);
	while (i > k)
	{
		if (ft_strncmp(ms->tokens[k], "|", 1) != 0)
			new_tokens[k] = ms->tokens[k];
		k++;
	}
	new_tokens[k] = NULL;
	ms->tokens = new_tokens;
}

/*Check for pipes*/

int	ft_has_pipe(char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			if (str[i] == '|')
			{
				printf("good");
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}

int	ft_exect_pipes(t_minishell *ms)
{
	char	*cmd;
	
	if (ft_has_pipes(ms->tokens))
	{
		
	}
}
