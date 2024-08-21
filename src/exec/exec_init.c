/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:46:05 by akretov           #+#    #+#             */
/*   Updated: 2024/08/21 16:17:01 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command_args(t_pipex *pipex, t_tokenlist *curr)
{
	if (pipex->cmd_args)
		free_cmd_args(pipex);
	if (pipex->cmd)
	{
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
	pipex->cmd_args = ft_get_arg(pipex, &curr);
	if (!pipex->cmd_args)
	{
		handle_exec_error(pipex, "Failed to get command arguments", "");
		return (1);
	}
	if (pipex->cmd_args[0])
	{
		if (ft_strchr(pipex->cmd_args[0], '/'))
			pipex->cmd = ft_strdup(pipex->cmd_args[0]);
		else
			pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		if (pipex->cmd_args[0] == NULL || pipex->cmd == NULL)
			return (1);
	}
	return (0);
}

int	init_pid(t_pipex *pipex, int n_pipes)
{
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * (n_pipes + 1));
	if (!pipex->pid)
	{
		msg("Memory allocation error");
		exit (EX_GENERAL_ERROR);
	}
	return (0);
}

void	init_pipex(t_mshell *msh)
{
	msh->pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (msh->pipex == NULL)
	{
		msg(ERR_MEMORY);
		exit(EX_GENERAL_ERROR);
	}
	msh->pipex->fd_pipe[0] = 0;
	msh->pipex->fd_pipe[1] = 0;
	msh->pipex->fd_in = dup(STDIN_FILENO);
	msh->pipex->fd_out = dup(STDOUT_FILENO);
	msh->pipex->cmd_paths = ft_split(*msh->path, ':');
	if (!msh->pipex->cmd_paths)
	{
		msh->pipex->cmd_paths = NULL;
		return ;
	}
	msh->pipex->status = 0;
	msh->pipex->cmd = NULL;
	msh->pipex->cmd_args = NULL;
	msh->pipex->pid = NULL;
	msh->pipex->rd_flag = false;
}
