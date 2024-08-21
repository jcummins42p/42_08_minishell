/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_pr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/21 16:22:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_fail(t_mshell *msh, t_tokenlist *curr)
{
	handle_exec_error(msh->pipex, "command not found", curr->expand);
	close_curr_fd(msh->pipex, 1);
	free_pipex(msh->pipex);
	input_cleanup(msh);
	shell_free(msh);
}

void	dup2_check(int oldfd, int newfd, char *error_msg, t_pipex *pipex)
{
	if (dup2(oldfd, newfd) == -1)
	{
		handle_exec_error(pipex, error_msg, "");
		exit(EXIT_FAILURE);
	}
}

void	child(t_pipex *pipex, t_mshell *msh, int curr_pipe)
{
	t_tokenlist	*curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);
	dup2_check(pipex->fd_in, STDIN_FILENO, ERR_STDIN, pipex);
	close_two_pipes(pipex->fd_pipe[0], pipex->fd_in);
	if (pipex->rd_flag)
		dup2_check(pipex->fd_out, STDOUT_FILENO, ERR_STDOUT, pipex);
	else
		dup2_check(pipex->fd_pipe[1], STDOUT_FILENO, ERR_STDOUT, pipex);
	close_two_pipes(pipex->fd_out, pipex->fd_pipe[1]);
	if (!exec_builtin(msh, curr))
		exit(EX_SUCCESS);
	if (!pipex->cmd)
		execve_fail(msh, curr);
	else if (execve(pipex->cmd, pipex->cmd_args, msh->env) < 0)
		handle_exec_error(pipex, "command not found", curr->expand);
	exit(EX_COMMAND_NOT_FOUND);
}

void	last_child(t_pipex *pipex, t_mshell *msh, int curr_pipe)
{
	t_tokenlist	*curr;

	curr = token_after_pipeno(&msh->tokens, curr_pipe);
	close_two_pipes(pipex->fd_pipe[1], pipex->fd_pipe[0]);
	dup2_check(pipex->fd_in, STDIN_FILENO, ERR_STDIN, pipex);
	dup2_check(pipex->fd_out, STDOUT_FILENO, ERR_STDOUT, pipex);
	close_two_pipes(pipex->fd_in, pipex->fd_out);
	if (!exec_builtin(msh, curr))
		exit(EX_SUCCESS);
	if (!pipex->cmd)
		execve_fail(msh, curr);
	else if (execve(pipex->cmd, pipex->cmd_args, msh->env))
		handle_exec_error(pipex, "command not found", curr->expand);
	exit(EX_COMMAND_NOT_FOUND);
}
