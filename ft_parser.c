/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:33:17 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/05 13:13:03 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  < "ls -l" | wc -l

/* to do
handle :
➜  ~ echo "hello '$USER'"
hello 'ccodere'
➜  ~ echo hello '$USER'
hello $USER

*/
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
int	ft_trim_quotes(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;
	char	*res;

	t = &(ms->token);
	while (ft_is_dquote(line[i]))
		i++;
	while (!ft_isspace(line[i]) && line[i + 1])
		i++;
	(*t).end = i + 1;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	res = ft_strpass(substr, '"', ((*t).end - (*t).start));
	free(substr);
	ms->args[k] = res;
	(*t).in_dquotes = FALSE;
	if (line[i + 1])
		i++;
	return (i + 1);
}

int	ft_quotes_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	while (line[i] && ft_is_dquote(line[i]))
		i++;
	(*t).start = i;
	while (line[i] && !ft_is_dquote(line[i]))
		i++;
	if ((ft_is_dquote(line[i]) && (ft_is_dquote(line[i + 1])))
		|| (ft_is_dquote(line[i]) && !ft_isspace(line[i + 1])))
		i = ft_trim_quotes(ms, line, i, k);
	else if (ft_is_dquote(line[i]) && !ft_is_dquote(line[i + 1]))
	{
		(*t).end = i;
		ms->args[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
		(*t).in_dquotes = FALSE;
		i++;
	}
	return (i);
}

int	ft_normal_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;

	t = &(ms->token);
	if (line[i] && !(*t).in_dquotes)
	{
		(*t).start = i;
		while (line[i] && !ft_isspace(line[i]) && !ft_isquotes(line[i]))
			i++;
		while (ft_is_dquote(line[i]) && !ft_isspace(line[i + 1]))
			i++;
		(*t).end = i;
		substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
		ms->args[k] = substr;
	}
	return (i);
}

void	ft_init_token(t_minishell *ms, char *line, int i, int k)
{
	ms->args = malloc(sizeof(char *) * BUFFER_SIZE);
	if (!line)
		ms->args[k] = ft_strdup("");
	if (ft_charcount(line, '"') % 2 != 0)
	{
		ft_fprintf(2, "ms: open dbl quote error\n");
		return ;
	}
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		while (ft_isspace(line[i]) && !ms->token.in_dquotes)
			i++;
		if (ft_isquotes(line[i]) && !ms->token.in_dquotes)
		{
			ms->token.in_dquotes = TRUE;
			i = ft_quotes_token(ms, line, i, k);
		}
		else
			i = ft_normal_token(ms, line, i, k);
		k++;
	}
	ms->args[k] = NULL;
}