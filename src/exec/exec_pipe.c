/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/03 18:31:58 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[0]); // Close unused read end
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdin\n");
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdout\n");
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, "Execve failed\n");
}

void last_child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[1]); // Close the unused write end

	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdin\n");
	close(pipex->fd_pipe[0]); // Close the unused read end

	// Last child outputs to the specified output or terminal
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdout\n");
	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, "Execve failed\n");
}
