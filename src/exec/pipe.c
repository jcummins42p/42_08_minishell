/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/07/24 17:58:31 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec_error(t_pipex *pipex, const char *error_message)
{
	(void)pipex;
	/*free_pipex(pipex);*/
	msg(error_message);
	exit(1);
}

void child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[0]); // Close unused read end
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdin");
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdout");
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, "Execve failed");
}

void last_child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[1]); // Close the unused write end

	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdin");
	close(pipex->fd_pipe[0]); // Close the unused read end

	// Last child outputs to the specified output or terminal
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdout");
	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, "Execve failed");
}

void ft_pipe(int number_pipes, char *av[], char *env[], t_pipex *pipex)
{
	int i;
	int j;

	i = number_pipes + 1;
	j = 0;

	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * i);
	if (!pipex->pid)
	{
		msg("Memory allocation error");
		return;
	}
	pipex->fd_in = dup(STDIN_FILENO); // Start reading from stdin initially
	pipex->fd_out = dup(STDOUT_FILENO); // Save original stdout
	while (j < i)
	{
		pipex->cmd_args = ft_split(av[j], ' ');
		if (!pipex->cmd_args) {
			msg("Command split error");
			free_pipex(pipex);
			return;
		}
		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		if (!pipex->cmd) {
			msg("Command not found");
			free_pipex(pipex);
			return;
		}
		if (j < i - 1) { // For all commands except the last one
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, "Pipe creation error");
		}

		pipex->pid[j] = fork();
		if (pipex->pid[j] < 0) {
			handle_exec_error(pipex, "Fork error");
		}

		if (pipex->pid[j] == 0)
		{ // Child process
			if (j == i - 1) { // Last command
				last_child(pipex, env);
			} else {
				child(pipex, env);
			}
		}
	// Parent process: Close write end and update fd_in for next child
		close(pipex->fd_pipe[1]);
		close(pipex->fd_in);

	// For the next command, fd_in becomes the read end of the current pipe
		if (j < i - 1)
			pipex->fd_in = pipex->fd_pipe[0];
		j++;
	}
	// Wait for all child processes to complete
	for (int k = 0; k < number_pipes + 1; k++)
		waitpid(pipex->pid[k], NULL, 0);

	close(pipex->fd_in);
	close(pipex->fd_out);
	free_pipex(pipex);
}
