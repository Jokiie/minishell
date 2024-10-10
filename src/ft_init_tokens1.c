/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tokens1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:24:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/10 16:48:41 by matislessar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* 

I KNOW my file is huge but im currently working on it. -_-

Finally handle doublequote and singlequote... but no with this combinaison : 
ccodere/minishell ➜ echo 'hello'hello"hello"
expected output : hellohellohello

also need to make the single quote not change the variable if not in a dblquote string :
ccodere/minishell ➜ echo "hello '$USER'"
expected output : hello 'ccodere'
ccodere/minishell ➜ echo hello '$USER'
expected output : hello $USER

*/
int	ft_trim_dquotes(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;
	char	*res;

	t = &(ms->token);
	while (ft_is_dquote(line[i]))
	{
		i++;
		(*t).in_dquotes = !(*t).in_dquotes;
	}
	if (!(*t).in_dquotes)
	{	
		while (!ft_isspace(line[i]) && line[i] != '\0')
			i++;
	}
	else
	{
		while (!ft_is_dquote(line[i]))
			i++;
		(*t).in_dquotes = !(*t).in_dquotes;
	}
	(*t).end = i + 1;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	res = ft_strpasses(substr, "\'\"", ((*t).end - (*t).start));
	free(substr);
	ms->tokens[k] = res;
	(*t).in_dquotes = !(*t).in_dquotes;
	if (line[i + 1])
		i++;
	return (i + 1);
}

int	ft_trim_squotes(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;
	char	*substr;
	char	*res;

	t = &(ms->token);
	while (ft_is_squote(line[i]))
		i++;
	if (!(*t).in_squotes)
	{	
		while (!ft_isspace(line[i]) && line[i] != '\0')
			i++;
	}
	else
	{
		while (!ft_is_squote(line[i]))
			i++;
		(*t).in_squotes = !(*t).in_squotes;
	}
	(*t).end = i + 1;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	res = ft_strpasses(substr, "\'\"", ((*t).end - (*t).start));
	free(substr);
	ms->tokens[k] = res;
	(*t).in_squotes = !(*t).in_squotes;
	if (line[i + 1])
		i++;
	return (i + 1);
}

int	ft_squote_token(t_minishell *ms, char *line, int i, int k)
{
	t_token *t;

	t = &(ms->token);
	while (ft_is_squote(line[i]))
		i++;
	(*t).start = i;
	while(line[i])
	{
		if ((ft_is_squote(line[i]) && (ft_is_squote(line[i + 1])))
			|| (ft_is_squote(line[i]) && !ft_isspace(line[i + 1])))
		{
			i = ft_trim_squotes(ms, line, i, k);
			return (i);
		}
		else if (ft_is_squote(line[i]) && ft_isspace(line[i + 1]))
		{
			(*t).end = i;
			ms->tokens[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
			(*t).in_squotes = !(*t).in_squotes;
			return (i + 1);
		}
		i++;
	}
	return (i);	
}

int	ft_dquotes_token(t_minishell *ms, char *line, int i, int k)
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
			i = ft_trim_dquotes(ms, line, i, k);
			return (i);
		}
		else if (ft_is_dquote(line[i]) && ft_isspace(line[i + 1]))
		{
			(*t).end = i;
			ms->tokens[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
			(*t).in_dquotes = !(*t).in_dquotes;
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
		if (ft_isspace(line[i]) && (!(*t).in_dquotes || !(*t).in_squotes))
			break ;
		if (ft_isquotes(line[i]))
		{
			if (ft_is_dquote(line[i]))
			{
				(*t).in_dquotes = !(*t).in_dquotes;
				i = ft_trim_dquotes(ms, line, i, k);
			}
			else if (ft_is_squote(line[i]))
			{
				(*t).in_squotes = !(*t).in_squotes;
				i = ft_trim_squotes(ms, line, i, k);
			}
			i++;
		}
		else
			i++;
	}
	(*t).end = i;
	substr = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	res = ft_strpasses(substr, "\'\"", ((*t).end - (*t).start));
	free(substr);
	ms->tokens[k] = res;
	return (i);
}

int	ft_create_tokens(t_minishell *ms, char *line, int i, int k)
{
	ms->tokens = malloc(sizeof(char *) * BUFFER_SIZE);
	if (!line)
		ms->tokens[k] = ft_strdup("");
	if (ft_charcount(line, '"') % 2 != 0 || ft_charcount(line, '\'') % 2 != 0)
	{
		ft_fprintf(2, "ms: open quote error\n");
		return (FAIL);
	}
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (ft_is_dquote(line[i]))
		{
			ms->token.in_dquotes = !ms->token.in_dquotes;
			i = ft_dquotes_token(ms, line, i, k);
		}
		else if (ft_is_squote(line[i]) && !ms->token.in_dquotes)
		{
			ms->token.in_squotes = !ms->token.in_dquotes;
			i = ft_squote_token(ms, line, i, k);
		}
		else
			i = ft_normal_token(ms, line, i, k);
		k++;
	}
	ms->tokens[k] = NULL;
	return (SUCCESS);
}
