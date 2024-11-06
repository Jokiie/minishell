/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:26 by ccodere           #+#    #+#             */
/*   Updated: 2024/11/05 21:16:37 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int execute_heredocs(t_minishell *ms)
{
    int count;
    
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
	static int	count = -1;
	int			k;
	char		*tmp;
    char        *delim;

	k = 0;
    while (ms->tokens[k])
	{
		if (is_heredoc(ms->tokens[k]))
		{
			tmp = ms->tokens[k];
            delim = ms->tokens[k + 1];
			ms->ret = heredoc(ms, delim);
            if (ms->ret != SUCCESS)
                return (ERROR);
			ms->tokens[k] = ft_strdup(*ms->heredoc.fd_name[++count]);
			while (ms->tokens[k + 1]) // decal pour enlever le delim
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

int count_heredoc(t_minishell *ms)
{
    int k;
    int count;

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

int	heredoc(t_minishell *ms, char *delim)
{
	static int	i = -1;
	int			tmp_fd;

	(*ms->heredoc.fd_name[++i]) = create_heredoc_name();
    tmp_fd = open((*ms->heredoc.fd_name[i]), O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		ft_free(line);
	}
	// ft_free(line);
	return (SUCCESS);
}

char	*create_heredoc_name(void)
{
	static int	count = 0;
	char		*name;
	char		*num;

	num = ft_itoa(count);
	if (!num)
		return (NULL);
	name = ft_strjoin("./tmp/heredoc", num);
	free(num);
	count++;
	return (name);
}

void	unlink_heredocs(t_minishell *ms)
{
	int i;

	i = ms->heredoc.count;
	while (i > -1)
	{
		unlink(*ms->heredoc.fd_name[i]);
        ft_free(*ms->heredoc.fd_name[i]);
        i--;
	}
}