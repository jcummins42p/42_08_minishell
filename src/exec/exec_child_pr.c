/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_pr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/04 19:16:28 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_pipex *pipex, t_mshell *msh)
{
	close(pipex->fd_pipe[0]); // Close unused read end
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, ERR_STDIN);
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		handle_exec_error(pipex, ERR_STDOUT);
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (execve(pipex->cmd, pipex->cmd_args, msh->env) < 0) //add condition either execve or builtin
		handle_exec_error(pipex, "Execve failed\n");
}

void	last_child(t_pipex *pipex, t_mshell *msh, int n_pipes)
{
	if (n_pipes != 0)
	{
		close(pipex->fd_pipe[1]); // Close the unused write end
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			handle_exec_error(pipex, ERR_STDIN);
		close(pipex->fd_pipe[0]); // Close the unused read end
	}
	else 
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			handle_exec_error(pipex, ERR_STDIN);

	// Last child outputs to the specified output or terminal
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		handle_exec_error(pipex, ERR_STDOUT);
	if (!exec_builtin(msh, msh->tokens))
		return ;
	else 
		if (execve(pipex->cmd, pipex->cmd_args, msh->env) < 0) //add condition either execve or builtin
			handle_exec_error(pipex, "Execve failed\n");
}
