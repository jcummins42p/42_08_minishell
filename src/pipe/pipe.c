/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/07/23 14:05:07 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// void	ft_pipe(int ac ,char *av[], char *envp[], t_pipex *pipex)
// {
// 	pipex->pid1 = fork();
// 	if (pipex->pid1 == 0)
// 	{
// 		first_child(pipex, av, envp);
// 		close(pipex->fd_pipe[0]);
// 		close(pipex->fd_pipe[1]);
// 	}
// 	while (ac > 0)
// 	{
// 		pipex->pid2 = fork();
// 		if (ac == 1)
// 		{
// 			if (pipex->pid2 == 0)
// 			{
// 				last_child(pipex, av, envp);
// 			}
// 			close(pipex->fd_pipe[0]);
// 			close(pipex->fd_pipe[1]);
// 		}
// 		else
// 		{
// 			if (pipex->pid2 == 0)
// 			{
// 				middle_child(pipex, av, envp);
// 			}
// 			close(pipex->fd_pipe[0]);
// 			close(pipex->fd_pipe[1]);
// 		}
// 		waitpid(pipex->pid2, NULL, 0);
// 		ac--;
// 	}
// 	close_pipes(pipex);
// 	waitpid(pipex->pid1, NULL, 0);
// 	waitpid(pipex->pid2, NULL, 0);
// 	child_free(pipex);
// 	parent_free(pipex);
// 	free(pipex);
// }
