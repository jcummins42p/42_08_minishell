/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/08/19 15:36:07 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_finish(t_mshell *msh, t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < (msh->info->n_pipe + 1))
		waitpid(pipex->pid[i], &msh->exitcode, 0);
	if (WIFEXITED(msh->exitcode))
		msh->exitcode = WEXITSTATUS(msh->exitcode);
}

void	fork_and_execute(t_pipex *pipex, t_mshell *msh, int j)
{
	pipex->pid[j] = fork();
	if (pipex->pid[j] < 0)
		handle_exec_error(pipex, "Fork error", "");
	if (pipex->pid[j] == 0)
	{
		if (j == msh->info->n_pipe)
			last_child(pipex, msh, j);
		else
			child(pipex, msh, j);
	}
}

int	execute_commands(t_mshell *msh, t_pipex *pipex, int j)
{
	t_tokenlist	*curr;

	curr = NULL;
	curr = token_after_pipeno(&msh->tokens, j);
	pipex->rd_flag = false;
	if (do_redirection(msh, curr))
		return (++j);
	else if (msh->info->n_pipe == 0 && !exec_builtin(msh, msh->tokens))
		return (-1);
	init_command_args(pipex, curr);
	if (pipex->cmd_args[0] == NULL)
		return (++j);
	if (msh->info->n_pipe != 0 || j == msh->info->n_pipe)
		if (pipe(pipex->fd_pipe) < 0)
			handle_exec_error(pipex, "Pipe creation error", "");
	fork_and_execute(pipex, msh, j);
	close_two_pipes(pipex->fd_in, pipex->fd_out);
	if (j < msh->info->n_pipe)
	{
		pipex->fd_in = dup(pipex->fd_pipe[0]);
		close_two_pipes(pipex->fd_pipe[0], pipex->fd_pipe[1]);
	}
	else
		pipex->fd_in = dup(STDIN_FILENO);
	pipex->fd_out = dup(STDOUT_FILENO);
	return (++j);
}

void	ft_exec_cmd(t_mshell *msh)
{
	t_pipex		*pipex;
	int			j;
	int			temp;

	temp = 0;
	j = 0;
	pipex = msh->pipex;
	if (init_pid(pipex, msh->info->n_pipe))
		return ;
	while (j >= 0 && j <= msh->info->n_pipe)
	{
		j = execute_commands(msh, pipex, j);
	}
	if (j != -1)
		execute_finish(msh, pipex);
}
