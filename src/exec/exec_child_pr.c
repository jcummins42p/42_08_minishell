/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_pr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/16 17:31:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child(t_pipex *pipex, t_mshell *msh, int curr_pipe)
{
	t_tokenlist *curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);

	// Close unused pipe ends
	close(pipex->fd_pipe[0]);

	// Redirect input
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
	{
		handle_exec_error(pipex, ERR_STDIN, "");
		exit(EXIT_FAILURE);
	}
	close(pipex->fd_in);

	// Redirect output
	if (pipex->rd_flag)
	{
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		{
			handle_exec_error(pipex, ERR_STDOUT, "");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		{
			handle_exec_error(pipex, ERR_STDOUT, "");
			exit(EXIT_FAILURE);
		}
	}
	close(pipex->fd_out);
	close(pipex->fd_pipe[1]);
	if (!exec_builtin(msh, curr))
		exit(EX_SUCCESS);
	if (!pipex->cmd)
	{
		handle_exec_error(pipex, "command not found", curr->expand);
		close_curr_fd(msh->pipex, 1);
		free_pipex(pipex);
		input_cleanup(msh);
		shell_free(msh);
		exit(EX_COMMAND_NOT_FOUND);
	}
	// Execute the command using execve. If execve fails, handle the error and exit
	else if (execve(pipex->cmd, pipex->cmd_args, msh->env) < 0)
	{
		handle_exec_error(pipex, "command not found", curr->expand);
		exit(EX_COMMAND_NOT_FOUND);
	}
}

void last_child(t_pipex *pipex, t_mshell *msh, int curr_pipe)
{
	t_tokenlist *curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);

	close(pipex->fd_pipe[1]);
	close(pipex->fd_pipe[0]);
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
	{
		handle_exec_error(pipex, ERR_STDIN, "");
		exit(EXIT_FAILURE);
	}
	close(pipex->fd_in);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
	{
		handle_exec_error(pipex, ERR_STDOUT, "");
		exit(EXIT_FAILURE);
	}
	close(pipex->fd_out);

	if (!exec_builtin(msh, curr))
		exit(EX_SUCCESS);
	if (!pipex->cmd)
	{
		handle_exec_error(pipex, "command not found", curr->expand);
		close_curr_fd(msh->pipex, 1);
		free_pipex(pipex);
		input_cleanup(msh);
		shell_free(msh);
		exit(EX_COMMAND_NOT_FOUND);
	}
	else if (execve(pipex->cmd, pipex->cmd_args, msh->env))
	{
		handle_exec_error(pipex, "command not found", curr->expand);
		exit(EX_COMMAND_NOT_FOUND);
	}
}
