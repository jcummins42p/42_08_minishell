/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:46:05 by akretov           #+#    #+#             */
/*   Updated: 2024/08/16 13:15:21 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command_args(t_pipex *pipex, t_tokenlist *curr)
{
	free_cmd_args(pipex);
	free(pipex->cmd);
	pipex->cmd_args = ft_get_arg(pipex, &curr);
	if (!pipex->cmd_args || pipex->cmd_args[0] == NULL)
	{
		handle_exec_error(pipex, "Failed to get command arguments", "");
		return (1);
	}
	if (ft_strchr(pipex->cmd_args[0], '/'))
		pipex->cmd = ft_strdup(pipex->cmd_args[0]);
	else
		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
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
	msh->pipex->fd_in = dup(STDIN_FILENO);
	msh->pipex->fd_out = dup(STDOUT_FILENO);
	msh->pipex->cmd_paths = ft_split(*msh->path, ':');
	if (!msh->pipex->cmd_paths)
	{
		// add error handler
		return ;
	}
	msh->pipex->status = 0;
	msh->pipex->cmd = NULL;
	msh->pipex->cmd_args = NULL;
	msh->pipex->pid = NULL;
	msh->pipex->rd_flag = false;
}
