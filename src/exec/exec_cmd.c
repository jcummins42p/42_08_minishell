/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/08/05 17:56:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_execute(t_pipex *pipex, t_mshell *msh, int j)
{
	pipex->pid[j] = fork();
	if (pipex->pid[j] < 0)
		handle_exec_error(pipex, "Fork error\n");
	if (pipex->pid[j] == 0)
	{
		if (j == msh->info->n_pipe)
			last_child(pipex, msh, msh->info->n_pipe);
		else
			child(pipex, msh);
	}
}

void	execute_commands(t_mshell *msh, t_pipex *pipex)
{
	int j;

	j = 0;
	while (j < msh->info->n_pipe + 1)
	{
		pipex->cmd_args = ft_get_arg(pipex, &msh->tokens);
		if (!pipex->cmd_args)
			handle_exec_error(pipex, "Failed to get command arguments\n");

		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		if (!pipex->cmd)
			handle_exec_error(pipex, "Command not found\n");
		if (msh->info->n_pipe != 0)
		{
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, "Pipe creation error\n");
		}
		fork_and_execute(pipex, msh, j);
		if (j < msh->info->n_pipe)
		{
			close(pipex->fd_pipe[1]);
			pipex->fd_in = pipex->fd_pipe[0];
		}
		j++;
	}
}

void	ft_exec_cmd(t_mshell *msh)
{
	t_pipex	*pipex;

	pipex = msh->pipex;
	if (msh->info->n_pipe == 0 && !exec_builtin(msh, msh->tokens))
		return ;
	if (!init_pid(pipex, msh->info->n_pipe))
		return ;
	execute_commands(msh, pipex);
	cleanup(pipex, msh->info->n_pipe);
}
