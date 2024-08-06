/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_pr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/06 12:49:21 by jcummins         ###   ########.fr       */
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
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (!exec_builtin(msh, curr, STDOUT_FILENO))
		exit (1);
	else
		if (execve(pipex->cmd, pipex->cmd_args, msh->env) < 0) //add condition either execve or builtin
			handle_exec_error(pipex, "command not found", curr->expand);
}

void	last_child(t_pipex *pipex, t_mshell *msh, int n_pipes, int curr_pipe)
{
	t_tokenlist	*curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);
	if (n_pipes != 0)
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
	if (!exec_builtin(msh, curr, pipex->fd_out))
		exit (1);
	else
		if (execve(pipex->cmd, pipex->cmd_args, msh->env) < 0) //add condition either execve or builtin
			handle_exec_error(pipex, "command not found", curr->expand);
}
