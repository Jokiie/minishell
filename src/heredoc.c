/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/11 17:50:04 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_heredocs(t_minishell *ms)
{
	int	count;

	ms->heredoc.count = count_heredoc(ms);
	if (ms->heredoc.count > 42)
	{
		ft_fprintf(2, GREY"ms: reached maximum of heredocs(42)\n"RESET);
		return (ERROR);
	}
	else if (ms->heredoc.count == 0)
		return (SUCCESS);
	count = ms->heredoc.count;
	while (count > 1)
	{
		ms->ret = exec_heredoc(ms);
		count--;
	}
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
			check_delim(ms, k + 1);
			if (heredoc(ms, delim) != SUCCESS)
				return (ERROR);
			ms->tokens[k] = ft_strdup(ms->heredoc.fd_name[i]);
			k = shift_tokens(ms, &k);
			ft_free(delim);
			ft_free(tmp);
		}
		k++;
	}
	ms->tokc = count_tokens(ms->tokens);
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
	fill_heredoc(ms, tmp_fd, delim);
	close(tmp_fd);
	return (SUCCESS);
}

void	fill_heredoc(t_minishell *ms, int fd, char *delim)
{
	char	*line;
	char	*tmp_line;

	while (1)
	{
		init_signals_interactive();
		line = readline("> ");
		init_signals_noninteractive();
		tmp_line = expand_line(ms, line);
		if (check_line(tmp_line, delim) == FALSE)
			break ;
		ft_putendl_fd(tmp_line, fd);
		ft_free(tmp_line);
	}
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
