/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:50:45 by akretov           #+#    #+#             */
/*   Updated: 2024/08/18 17:05:47 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_two_pipes(int fd_1, int fd_2)
{
	close(fd_1);
	close(fd_2);
}

void	close_curr_fd(t_pipex *pipex, bool free_all)
{
	struct stat	st;

	if (fstat(pipex->fd_in, &st) == 0)
		close(pipex->fd_in);
	if (fstat(pipex->fd_out, &st) == 0)
		close(pipex->fd_out);
	if (free_all)
	{
		if (fstat(pipex->fd_pipe[0], &st) == 0)
			close(pipex->fd_pipe[0]);
		if (fstat(pipex->fd_pipe[1], &st) == 0)
			close(pipex->fd_pipe[1]);
	}
}

void	free_cmd_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->cmd_paths)
		return ;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	pipex->cmd_paths = NULL;
}

void	free_cmd_args(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->cmd_args)
		return ;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	pipex->cmd_args = NULL;
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->fd_pipe[0])
		close_curr_fd(pipex, 1);
	else
		close_curr_fd(pipex, 0);
	free_cmd_paths(pipex);
	free_cmd_args(pipex);
	free(pipex->cmd);
	free(pipex->pid);
	free(pipex);
}
