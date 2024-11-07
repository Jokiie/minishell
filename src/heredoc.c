/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/06 22:08:54 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_heredocs(t_minishell *ms)
{
	int	count;

	ms->heredoc.count = count_heredoc(ms);
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
		if (is_heredoc(ms->tokens[k]))
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
	ms->heredoc.fd_name[i] = create_heredoc_name();
	tmp_fd = open(ms->heredoc.fd_name[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		ft_fprintf(2, "Error tmp_fd\n");
		return (ERROR);
	}
	ms->ret = fill_heredoc(tmp_fd, delim);
	close(tmp_fd);
	return (ms->ret);
}

int	fill_heredoc(int fd, char *delim)
{
	char	*line;

	line = NULL;
	while (1)
	{
		init_signals_interactive();
		line = readline("> ");
		init_signals_noninteractive();
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		ft_free(line);
	}
	return (SUCCESS);
}

char	*create_heredoc_name(void)
{
	char	*name;
	char	*num;
	int		count;

	count = update_heredoc_number(FALSE);
	num = ft_itoa(count);
	name = ft_strjoin("./tmp/heredoc", num);
	free(num);
	return (name);
}
