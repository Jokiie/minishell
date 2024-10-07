/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:24:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/06 23:57:35 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* to do
handle :

➜  ~ echo "hello '$USER'"
hello 'ccodere'
➜  ~ echo hello '$USER'
hello $USER

 "/usr/bin/ls" -l
"string" "string"
  < "ls -l" | wc -l
*/
int	ft_trim_quotes(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;
	char	*res;

	t = &(ms->token);
	while (line[i + 1] && ft_is_dquote(line[i]))
		i++;
	while (line[i + 1] && !ft_isspace(line[i]))
		i++;
	(*t).end = i + 1;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	res = ft_strpass(substr, '"', ((*t).end - (*t).start));
	free(substr);
	ms->tokens[k] = res;
	(*t).in_dquotes = FALSE;
	if (line[i + 1])
		i++;
	return (i + 1);
}

int	ft_quotes_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	while (ft_is_dquote(line[i]))
		i++;
	(*t).start = i;
	while (line[i])
	{
		if ((ft_is_dquote(line[i]) && (ft_is_dquote(line[i + 1])))
			|| (ft_is_dquote(line[i]) && !ft_isspace(line[i + 1])))
		{
			i = ft_trim_quotes(ms, line, i, k);
			return (i);
		}
		else if (ft_is_dquote(line[i]) && ft_isspace(line[i + 1]))
		{
			(*t).end = i;
			ms->tokens[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
			(*t).in_dquotes = FALSE;
			return (i + 1);
		}
		i++;
	}
	return (i);
}

int	ft_normal_token(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;
	char	*res;

	t = &(ms->token);
	(*t).start = i;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && !ft_is_dquote(line[i]))
			i++;
		if (ft_isspace(line[i]) && !(t)->in_dquotes)
			break ;
		if (ft_is_dquote(line[i]) && line[i + 1] != '\0')
		{
			i++;
			(*t).in_dquotes = TRUE;
		}
		if (line[i] != '\0' && ft_is_dquote(line[i]))
			i++;
		(*t).in_dquotes = FALSE;
	}
	(*t).end = i;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	res = ft_strpass(substr, '"', ((*t).end - (*t).start));
	free(substr);
	ms->tokens[k] = res;
	return (i);
}

int	ft_create_tokens(t_minishell *ms, char *line, int i, int k)
{
	ms->tokens = malloc(sizeof(char *) * BUFFER_SIZE);
	if (!line)
		ms->tokens[k] = ft_strdup("");
	if (ft_charcount(line, '"') % 2 != 0)
	{
		ft_fprintf(2, "ms: open dbl quote error\n");
		return (1);
	}
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (ft_isquotes(line[i]))
		{
			ms->token.in_dquotes = !ms->token.in_dquotes;
			i = ft_quotes_token(ms, line, i, k);
		}
		else
			i = ft_normal_token(ms, line, i, k);
		k++;
	}
	ms->tokens[k] = NULL;
	return (0);
}
