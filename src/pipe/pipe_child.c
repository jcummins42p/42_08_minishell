/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:06:55 by akretov           #+#    #+#             */
/*   Updated: 2024/07/23 14:06:29 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	first_child(t_pipex *pipex, char *av[], char *envp[])
// {
// 	close(pipex->fd_pipe[0]);
// 	dup2(pipex->fd_pipe[1], 1);

// 	pipex->cmd_args = ft_split(av[0], ' ');
// 	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
// 	if (!pipex->cmd)
// 	{
// 		child_free(pipex);
// 		msg(ERR_CMD);
// 		exit(1);
// 	}
// 	if (execve(pipex->cmd, pipex->cmd_args, envp) < 0)
// 	{
// 		child_free(pipex);
// 		msg(ERR_EXEC);
// 		exit(1);
// 	}
// }

// void	last_child(t_pipex *pipex, char *av[], char *envp[])
// {
// 	close(pipex->fd_pipe[1]);
// 	dup2(pipex->fd_pipe[0], 0);
// 	// close(pipex->fd_pipe[0]);
// 	pipex->cmd_args = ft_split(av[1], ' ');
// 	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
// 	if (!pipex->cmd)
// 	{
// 		child_free(pipex);
// 		msg(ERR_CMD);
// 		exit(1);
// 	}
// 	if (!execve(pipex->cmd, pipex->cmd_args, envp))
// 	{
// 		child_free(pipex);
// 		msg(ERR_EXEC);
// 		exit(1);
// 	}
// }
