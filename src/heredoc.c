/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/08 14:41:18 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_heredocs(t_minishell *ms)
{
	int	count;

	ms->heredoc.count = count_heredoc(ms);
	if (ms->heredoc.count > 42)
	{
		ft_fprintf(2, "ms: reached maximum of heredocs(42)\n");
		ms->ret = ERROR;
		return (ms->ret);
	}
	count = ms->heredoc.count;
	if (count > 1)
	{
		while (count != 0)
		{
			ms->ret = exec_heredoc(ms);
			count--;
		}
	}
	else
		ms->ret = exec_heredoc(ms);
	return (ms->ret);
}

int	exec_heredoc(t_minishell *ms)
{
	int		i;
	int		k;
	char	*tmp;
	char	*delim;

	k = 0;
	i = update_heredoc_count(FALSE);
	while (ms->tokens[k])
	{
		if (is_heredoc(ms->tokens[k]) && ms->token.protected[k] == 0)
		{
			tmp = ms->tokens[k];
			delim = ms->tokens[k + 1];
			ms->ret = heredoc(ms, delim);
			if (ms->ret != SUCCESS)
				return (ERROR);
			ms->tokens[k] = ft_strdup(ms->heredoc.fd_name[i]);
			while (ms->tokens[k + 1])
			{
				if (ms->tokens[k + 2])
					ms->tokens[k + 1] = ms->tokens[k + 2];
				else
				{
					ft_free(delim);
					ms->tokens[k + 1] = NULL;
				}
				k++;
			}
			ft_free(tmp);
		}
		k++;
	}
	return (SUCCESS);
}

int	heredoc(t_minishell *ms, char *delim)
{
	int	i;
	int	tmp_fd;

	i = update_heredoc_index(FALSE);
	ms->heredoc.fd_name[i] = create_heredoc_name(ms);
	tmp_fd = open(ms->heredoc.fd_name[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		ft_fprintf(2, "Error tmp_fd\n");
		return (ERROR);
	}
	ms->ret = fill_heredoc(ms, tmp_fd, delim);
	close(tmp_fd);
	return (ms->ret);
}

int	fill_heredoc(t_minishell *ms, int fd, char *delim)
{
	char	*line;
	char	*tmp_delim;
	char	*tmp_line;

	tmp_delim = check_delim(ms, delim);
	while (1)
	{
		init_signals_interactive();
		line = readline("> ");
		init_signals_noninteractive();
		tmp_line = expand_line(ms, line);
		if (check_line(tmp_line, tmp_delim) == FALSE)
			break ;
		ft_putendl_fd(tmp_line, fd);
		ft_free(tmp_line);
	}
	ft_free(tmp_delim);
	return (SUCCESS);
}

char	*check_delim(t_minishell *ms, char *delim)
{
	char *new_delim;

	if (has_quotes(delim))
	{
		ms->heredoc.in_quotes = TRUE;
		new_delim = ft_toktrim(ms, delim, ft_strlen(delim));
	}
	else if (!has_quotes(delim))
	{
		new_delim = ft_strdup(delim);
		ms->heredoc.in_quotes = FALSE;
	}
	ft_printf("heredoc in quotes?: %d\n", ms->heredoc.in_quotes);
	return (new_delim);
}

char	*create_heredoc_name(t_minishell *ms)
{
	char	*name;
	char	*num;
	char	*full_path;
	int		count;

	count = update_heredoc_number(FALSE);
	num = ft_itoa(count);
	full_path = ft_strjoin(ms->path, "/tmp/heredoc");
	name = ft_strjoin(full_path, num);
	free(full_path);
	free(num);
	return (name);
}

t_bool	check_line(char *line, char *delim)
{
	if (!line || ft_strcmp(line, delim) == 0)
	{
		if (!line)
			ft_fprintf(2,
				"ms: warning: here-document delimited by end-of-file (wanted '%s')\n",
				delim);
		free(line);
		return (FALSE);
	}
	return (TRUE);
}

char	*expand_line(t_minishell *ms, char *line)
{
	char	*tmp_line;

	if (!line)
		return (NULL);
	if (ms->heredoc.in_quotes == FALSE && ft_strchr(line, '$'))
	{
		tmp_line = expander(ms, line);
		if (tmp_line)
		{
			ft_free(line);
			line = tmp_line;
		}
		else
			ft_free(line);
	}
	return (line);
}

char	*expander(t_minishell *ms, char *line)
{
	char	*line_dup;
	char	*new_line_dup;
	int		i;

	i = 0;
	line_dup = ft_strdup(line);
	while (line_dup[i])
	{
		if (line_dup[i] == '$' && (ft_isalnum(line_dup[i + 1])
			|| line_dup[i + 1] == '_'))
		{
			new_line_dup = apply_var_expansion(line_dup, i);
			line_dup = new_line_dup;
		}
		else if (line_dup[i] == '$' && line_dup[i + 1] == '?')
		{
			new_line_dup = apply_nbr_expansion(ms, line_dup, i);
			line_dup = new_line_dup;
		}
		else
			i++;
	}
	return (line_dup);
}
