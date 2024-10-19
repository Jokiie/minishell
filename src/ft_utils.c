/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:33:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/19 00:13:12 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens || !*tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

void	ft_print_tokens(char **tokens)
{
	int	k;

	k = 0;
	if (!tokens || !*tokens)
		return ;
	while (tokens[k])
	{
		ft_printf(":%s:\n", tokens[k]);
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

	size = ft_count_tokens(envp);
	env_dup = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_dup)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i] && j < (size + 1))
		env_dup[j++] = ft_strdup(envp[i++]);
	env_dup[j] = NULL;
	return (env_dup);
}
