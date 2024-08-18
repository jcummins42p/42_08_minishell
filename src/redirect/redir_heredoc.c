/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:01 by akretov           #+#    #+#             */
/*   Updated: 2024/08/18 17:10:39 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	return (fd);
}

void	ft_handle_heredoc(t_pipex *pipex, const char *delimiter)
{
	char	*line;

	if (pipe(pipex->fd_pipe) == -1)
	{
		write(STDERR_FILENO, ERR_PIPE, 21);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL
			|| ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipex->fd_pipe[1], line, ft_strlen(line));
		write(pipex->fd_pipe[1], "\n", 1);
		free(line);
	}
	close_two_pipes(pipex->fd_pipe[1], pipex->fd_in);
	pipex->fd_in = dup(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[0]);
}
