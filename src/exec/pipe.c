/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/07/23 18:20:28 by jcummins         ###   ########.fr       */
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

void	first_child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[0]); // Close unused read end
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		handle_exec_error(pipex, ERR_EXEC);
	close(pipex->fd_pipe[1]); // Close the copy of write end

	if (!pipex->cmd)
		handle_exec_error(pipex, ERR_CMD);

	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, ERR_EXEC);
}

void	last_child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[1]); // Close unused write end
	if (dup2(pipex->fd_pipe[0], STDIN_FILENO) == -1)
		handle_exec_error(pipex, ERR_EXEC);
	close(pipex->fd_pipe[0]); // Close the copy of read end

	if (!pipex->cmd)
		handle_exec_error(pipex, ERR_CMD);

	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, ERR_EXEC);
}

void	ft_pipe(int number_pipes, char *av[], char *env[], t_pipex *pipex)
{
	int	i;
	int j;

	i = number_pipes + 1;
	j = 0;
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * i);
	if (!pipex->pid)
	{
		msg("Memory allocation error");
		return;
	}

	while (i > 0)
	{
		pipex->cmd_args = ft_split(av[j], ' ');
		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		printf("%s\n", pipex->cmd);
		if (i == 1)  // Last command
		{
			pipex->pid[j] = fork();
			if (pipex->pid[j] < 0)
				handle_exec_error(pipex, ERR_FORK);
			if (pipex->pid[j] == 0)
				last_child(pipex, env);
		}
		else
		{
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, ERR_PIPE);
			pipex->pid[j] = fork();
			if (pipex->pid[j] < 0)
				handle_exec_error(pipex, ERR_FORK);
			if (pipex->pid[j] == 0)
				first_child(pipex, env);
			else
			{
				close(pipex->fd_pipe[1]);
				dup2(pipex->fd_pipe[0], STDIN_FILENO);
				close(pipex->fd_pipe[0]);
			}
		}
		i--;
		j++;
	}

	// Wait for all child processes to complete
	for (int k = 0; k < number_pipes + 1; k++)
		waitpid(pipex->pid[k], NULL, 0);

	/*free_pipex(pipex);*/
	/*free(pipex->pid);*/
}
