/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:01 by akretov           #+#    #+#             */
/*   Updated: 2024/08/13 20:37:34 by akretov          ###   ########.fr       */
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
		write(STDERR_FILENO, "Couldn't create pipe\n", 22);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipex->fd_pipe[1], line, ft_strlen(line));
		write(pipex->fd_pipe[1], "\n", 1);
		free(line);
	}
	close(pipex->fd_pipe[1]);
}

int	ft_handle_redirection(t_pipex *pipex, t_tokenlist *tokens)
{
	if (tokens == NULL)
		return (1);
	if (tokens->mtctype == RDIN)
	{
		if (ft_handle_rdin(pipex, tokens) == 1)
			return (1);
	}
	else if (tokens->mtctype == RDOUT)
		ft_handle_rdout(pipex, tokens);
	else if (tokens->mtctype == RDAPP)
		ft_handle_app(pipex, tokens);
	else if (tokens->mtctype == DELIMIT)
	{
		tokens = tokens->next;
		if (tokens)
		{
			ft_handle_heredoc(pipex, tokens->token);
			pipex->fd_in = dup(pipex->fd_pipe[0]);
			close(pipex->fd_pipe[0]);
		}
	}
	if (tokens)
		tokens = tokens->next;
	return (0);
}
