/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/08/13 16:35:55 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_execute(t_pipex *pipex, t_mshell *msh, int j)
{
	pipex->pid[j] = fork();
	//	redefine singal handlers here if neccessary for child processes
	if (pipex->pid[j] < 0)
		handle_exec_error(pipex, "Fork error", "");
	if (pipex->pid[j] == 0)
	{
		// child process
		// setup_signal_handlers_child();
		if (j == msh->info->n_pipe)
			last_child(pipex, msh, j);
		else
			child(pipex, msh, j);
	}
}

void	execute_commands(t_mshell *msh, t_pipex *pipex)
{
	int 		j;
	int			i;
	t_tokenlist	*curr;
	t_tokenlist	*ptr_redirect;

	j = 0;
	curr = NULL;
	ptr_redirect = msh->tokens;
	while (j <= msh->info->n_pipe)
	{
		curr = token_after_pipeno(&msh->tokens, j);
		do_redirection(msh, curr);
		if (msh->info->n_pipe == 0 && !exec_builtin(msh, msh->tokens))
			return ;
		pipex->cmd_args = ft_get_arg(pipex, &curr);
		if (!pipex->cmd_args)
			handle_exec_error(pipex, "Failed to get command arguments", "");
		if (ft_strchr(pipex->cmd_args[0], '/'))
			pipex->cmd = pipex->cmd_args[0];
		else
			pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		if (msh->info->n_pipe != 0)
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, "Pipe creation error", "");
		fork_and_execute(pipex, msh, j);
		if (j < msh->info->n_pipe)
		{
			close(pipex->fd_pipe[1]);
			pipex->fd_in = pipex->fd_pipe[0];
		}
		j++;
		i = 0;
		while (pipex->cmd_args[i])
			free(pipex->cmd_args[i++]);
		free(pipex->cmd_args);
		pipex->cmd_args = NULL;
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
	i = 0;
	while (i < (msh->info->n_pipe + 1))
	{
		waitpid(pipex->pid[i], &msh->exitcode, 0);
		i++;
	}
	if (WIFEXITED(msh->exitcode))
		msh->exitcode = WEXITSTATUS(msh->exitcode);
}

void	ft_exec_cmd(t_mshell *msh)
{
	t_pipex	*pipex;

	pipex = msh->pipex;
	// if (msh->info->n_pipe == 0 && !exec_builtin(msh, msh->tokens, pipex->fd_out))
	// 	return ;
	if (init_pid(pipex, msh->info->n_pipe))
		return ;
	execute_commands(msh, pipex);
}
