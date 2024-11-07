/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/06 21:56:59 by ccodere          ###   ########.fr       */
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

int	count_heredoc(t_minishell *ms)
{
	int	k;
	int	count;

	count = 0;
	k = 0;
	while (ms->tokens[k])
	{
		if (is_heredoc(ms->tokens[k]))
			count++;
		k++;
	}
	return (count);
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

void	unlink_heredocs(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < 42 && ms->heredoc.fd_name[i] != NULL)
	{
		if (unlink(ms->heredoc.fd_name[i]) != 0)
			ft_fprintf(2, "ms: unlink failed for %s\n", ms->heredoc.fd_name[i]);
		i++;
	}
}

void	reset_heredoc(t_minishell *ms)
{
	unlink_heredocs(ms);
	clear_heredoc_names(ms);
	reset_heredoc_statics();
}

void	clear_heredoc_names(t_minishell *ms)
{
	int	i;
	int	all_freed;

	i = 0;
	all_freed = 1;
	while (i < 42 && ms->heredoc.fd_name[i] != NULL)
	{
		free(ms->heredoc.fd_name[i]);
		ms->heredoc.fd_name[i] = NULL;
	    i++;
	}
	for (int j = 0; j < 42; j++)
	{
		if (ms->heredoc.fd_name[j] != NULL)
		{
			all_freed = 0;
			break ;
		}
	}
	if (all_freed)
		ft_printf("Heredocs's name is empty\n");
	else
		ft_printf("Heredocs's name is not empty\n");
}

void	reset_heredoc_statics(void)
{
	update_heredoc_index(TRUE);
	update_heredoc_number(TRUE);
	update_heredoc_count(TRUE);
}

int	update_heredoc_index(t_bool reset)
{
	static int	count = -1;

	if (reset == TRUE)
    {
		count = -1;
        return (count);
    }
	return (++count);
}

int	update_heredoc_number(t_bool reset)
{
	static int	count = -1;

	if (reset == TRUE)
    {
        count = -1;
        return (count);
    }
	return (++count);
}

int	update_heredoc_count(t_bool reset)
{
	static int	count = -1;

	if (reset == TRUE)
    {
		count = -1;
        return (count);
    }
    return (++count);
}
