/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:33:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/25 13:51:58 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(char **tokens)
{
	int	k;

	k = 0;
	if (!tokens || !*tokens)
		return ;
	while (tokens[k])
	{
		ft_printf("%s\n", tokens[k]);
		k++;
	}
}

/*
	Dup the environment string tab
	to do: need to check if we can use it to remove a variable
	with unset and re-add it with export.
*/
char	**ft_envdup(char **envp)
{
	char	**env_dup;
	int		i;
	int		j;
	int		size;

	if (!envp && !*envp)
		return (NULL);
	size = count_tokens(envp);
	env_dup = ft_calloc(sizeof(char *), (size + 1));
	if (!env_dup)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i] && j < size)
		env_dup[j++] = ft_strdup(envp[i++]);
	env_dup[j] = NULL;
	return (env_dup);
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
