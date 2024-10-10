/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:24:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/10/10 02:50:24 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

int	separe_line(t_minishell *ms, char *line, int i, int k)
{
	t_token	*t;

	t = &(ms->token);
	(*t).start = i;
	while (ft_isquotes(line[i]))
	{
		i++;
		(*t).in_quotes = !(*t).in_quotes;
	}
	while (line[i])
	{	
		if (ft_isquotes(line[i]))
			(*t).in_quotes = !(*t).in_quotes;
		if ((ft_isquotes(line[i - 1]) && ft_isspace(line[i]))
			|| (ft_isquotes(line[i]) && line[i + 1] == '\0')
			|| (!(*t).in_quotes && ft_isspace(line[i])))
		{
			if (ft_isquotes(line[i]))
				(*t).in_quotes = !(*t).in_quotes;
			break ;
		}
		i++;
	}
	if (line[i + 1] == '\0' || ft_isspace(line[i + 1]))
		(*t).end = i + 1;
	else if (line[i] == '\0' || ft_isspace(line[i]) || ft_isquotes(line[i]))
		(*t).end = i;
	ms->tokens[k] = ft_substr(line, (*t).start, ((*t).end - (*t).start));
	return ((*t).end);
}

void	tokenizer(t_minishell *ms, char *line, int k)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		i = separe_line(ms, line, i, k);
		k++;
	}
	ms->tokens[k] = NULL;
}

void	trim_tokens(t_minishell *ms)
{
	int k;
	int	i;
	
	k = 0;
	while (ms->tokens[k])
	{
		while(ms->tokens[k][i])
		{
			if (ft_is_dquote(ms->tokens[k][i]) && !ms->token.in_squotes)
				ms->token.in_dquotes = !ms->token.in_dquotes;
			else if (ft_is_squote(ms->tokens[k][i]) && !ms->token.in_dquotes)
				ms->token.in_squotes = !ms->token.in_dquotes;
			i++;
		}
		if (ms->token.in_squotes)
			ms->tokens[k] = ft_strskip(ms->tokens[k], "\'", ft_strlen(ms->tokens[k]));
		else if (ms->token.in_dquotes)
			ms->tokens[k] = ft_strskip(ms->tokens[k], "\"", ft_strlen(ms->tokens[k]));
		k++;
	}
}

int	ft_create_tokens(t_minishell *ms, char *line)
{
	int	nbr_of_ptrs;
	int	k;
	
	nbr_of_ptrs = MB_SIZE / PTR_SIZE; // 2097152 / 8
	ms->tokens = (char **)malloc(sizeof(char *) * nbr_of_ptrs);
	k = 0;
	if (!line)
	{
		ms->tokens[0] = ft_strdup("");
		return (FAIL);
	}
	if (ft_charcount(line, '"') % 2 != 0 || ft_charcount(line, '\'') % 2 != 0)
	{
		ft_fprintf(2, "ms: open quote error\n");
		return (FAIL);
	}
	tokenizer(ms, line, k); // make ms->tokens
	characterize_tokens(ms); //need to rework to handle multiple var in a string
	trim_tokens(ms); // need to handle echo 'one "two" three'four"five"six"seven 'eight' nine"ten
	return (SUCCESS);
}


void	characterize_tokens(t_minishell *ms)
{
	int	k;
	
	k = 0;
	while (ms->tokens[k])
	{
		ms->tokens[k] = characterizer(ms, ms->tokens[k]);
		k++;
	}
}
char	*insert_variable_value(char *before, char *var, char *after)
{
	int		new_len;
	char	*var_value;
	char	*new_token;
	
	var_value = getenv(var);
	if (!var_value)
		var_value = "";
	new_len = ft_strlen(before) + ft_strlen(var_value) + ft_strlen(after) + 1;
	new_token = (char *)malloc(sizeof(char) * new_len);
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, before, new_len);
	ft_strlcat(new_token, var_value, new_len);
	ft_strlcat(new_token, after, new_len);
	return (new_token);
}

char	*characterizer(t_minishell *ms, char *token)
{
	int		i;
	char	*var;
	int		var_end;
	int		var_start;
	char	*before;
	char 	*after;
	char	*new_token;
	i = 0;

	while (token[i])
	{
		if (ft_is_dquote(token[i]) && !ms->token.in_squotes)
			ms->token.in_dquotes = !ms->token.in_dquotes;
		else if (ft_is_squote(token[i]) && !ms->token.in_dquotes)
			ms->token.in_squotes = !ms->token.in_dquotes;
		if (token[i] == '$' && !ms->token.in_squotes)
		{
			i++;
			var_start = i;
			while (!ft_isspace(token[i]) && !ft_isquotes(token[i]))
				i++;
			var_end = i;
			before = ft_substr(token, 0, (var_start - 1));
			//ft_printf("before : %s\n", before);
			while (token[i])
				i++;
			after = ft_substr(token, var_end, (i - var_end));
			//ft_printf("after : %s\n", after);
			var = ft_substr(token, var_start, (var_end - var_start));
			//ft_printf("var : %s\n", var);
			new_token = insert_variable_value(before, var, after);
			return (new_token);
		}
		i++;
	}
	return (token);
}
