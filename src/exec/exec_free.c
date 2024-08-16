/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:50:45 by akretov           #+#    #+#             */
/*   Updated: 2024/08/16 13:26:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(t_pipex *pipex)
{
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
	if (pipex->fd_pipe[0])
		close(pipex->fd_pipe[0]);
	if (pipex->fd_pipe[1])
		close(pipex->fd_pipe[1]);
	/*close(STDIN_FILENO);*/
	/*close(STDOUT_FILENO);*/
	/*close(STDERR_FILENO);*/
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

void	free_file_d(t_pipex *pipex)
{
	if (pipex->fd_in > 0)
		close(pipex->fd_in);
	if (pipex->fd_out > 0)
		close(pipex->fd_out);
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	close_all_fd(pipex);
	/*free_file_d(pipex);*/
	free_cmd_paths(pipex);
	free_cmd_args(pipex);
	free(pipex->cmd);
	free(pipex->pid);
	free(pipex);
}
