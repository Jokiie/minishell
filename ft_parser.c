/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:33:17 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/04 13:17:30 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  < "ls -l" | wc -l

int	ft_quotes_in_quotes(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	i++;
	if (ft_is_dquote(line[i]))
	{
		while (line[i] && ft_is_dquote(line[i]))
			i++;
		while (line[i] && !ft_is_dquote(line[i]))
			i++;
		if (ft_is_dquote(line[i]) && !ft_is_dquote(line[i + 1]))
		{
			(*t).end = i;
			ms->args[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
			(*t).in_dquotes = FALSE;
			i++;
		}
	}
	return (i);	
}

int	ft_quotes_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	if (ft_is_dquote(line[i]))
	{
		while (line[i] && ft_is_dquote(line[i]))
			i++;
		(*t).start = i;
		while (line[i] && !ft_is_dquote(line[i]))
			i++;
		if (ft_is_dquote(line[i]) && !ft_is_dquote(line[i + 1]))
		{
			(*t).end = i;
			ms->args[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
			(*t).in_dquotes = FALSE;
			i++;
		}
		else
		{
			ft_printf("There are 2 double quotes next to each other\n");
			exit(1);
		}
	}
	return (i);
}

int	ft_space_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	i++;
	(*t).start = i;
	while (line[i] && !ft_isspace(line[i]) && !ft_isquotes(line[i]))
		i++;
	if (ft_isspace(line[i]) || line[i] == '\0')
		(*t).end = i;
	ms->args[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	return (i);
}

int	ft_normal_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	if (line[i] && !(*t).in_dquotes)
	{
		if (i != 0)
        	i++;
		(*t).start = i;
		while (line[i] && !ft_isspace(line[i]) && !ft_isquotes(line[i]))
			i++;
		(*t).end = i;
		ms->args[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	}
	return (i);
}

void	ft_init_token(t_minishell *ms, char *line, int i, int k)
{
	ms->args = malloc(sizeof(char *) * BUFFER_SIZE);
	while (line[i])
	{
		if (ft_isquotes(line[i]) && !ms->token.in_dquotes)
		{
			ms->token.in_dquotes = TRUE;
			i = ft_quotes_token(ms, line, i, k);
		}
		else if (ft_isspace(line[i]) && !ms->token.in_dquotes)
		{
            if (!ft_is_dquote(line[i + 1]))
			    i = ft_space_token(ms, line, i, k);
            else
            {
                ms->token.in_dquotes = TRUE;
                i = ft_quotes_token(ms, line, i + 1, k);
            }
        }
		else
			i = ft_normal_token(ms, line, i, k);
		k++;
	}
	ms->args[k] = NULL;
}