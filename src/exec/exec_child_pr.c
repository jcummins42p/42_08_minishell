/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_pr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/15 13:51:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_pipex *pipex, t_mshell *msh, int curr_pipe)
{
	t_tokenlist	*curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);
	close(pipex->fd_pipe[0]); // Close unused read end
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, ERR_STDIN, "");
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		handle_exec_error(pipex, ERR_STDOUT, "");
	close(pipex->fd_in);
	close(pipex->fd_out);
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (!exec_builtin(msh, curr))
	{
		close_all_fd(msh->pipex);
		exit(EX_SUCCESS);
	}
	if (!pipex->cmd)
	{
		handle_exec_error(pipex, "command not found", curr->expand);
		close_all_fd(msh->pipex);
		free_pipex(pipex);
		input_cleanup(msh);
		shell_free(msh);
		exit(EX_COMMAND_NOT_FOUND);
	}
	else
		execve(pipex->cmd, pipex->cmd_args, msh->env);
}

void	last_child(t_pipex *pipex, t_mshell *msh, int curr_pipe)
{
	t_tokenlist	*curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);
	if (curr_pipe != 0)
	{
		close(pipex->fd_pipe[1]); // Close the unused write end
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			handle_exec_error(pipex, ERR_STDIN, "");
		close(pipex->fd_pipe[0]); // Close the unused read end
	}
	else
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			handle_exec_error(pipex, ERR_STDIN, "");
	// Last child outputs to the specified output or terminal
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		handle_exec_error(pipex, ERR_STDOUT, "");
	close(pipex->fd_in);
	close(pipex->fd_out);
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (!exec_builtin(msh, curr))
	{
		close(pipex->fd_pipe[0]);
		close_all_fd(msh->pipex);
		exit (EX_SUCCESS);
	}
	if (!pipex->cmd)
	{
		close(pipex->fd_pipe[0]);
		handle_exec_error(pipex, "command not found", curr->expand);
		close_all_fd(msh->pipex);
		free_pipex(pipex);
		input_cleanup(msh);
		shell_free(msh);
		exit(EX_COMMAND_NOT_FOUND);
	}
	else
	{
		close(pipex->fd_pipe[0]);
		execve(pipex->cmd, pipex->cmd_args, msh->env);
	}
}
