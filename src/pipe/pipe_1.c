/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/07/22 13:23:36 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	struct_init(t_pipex *pipex, char *envp[])
{
	if (pipe(pipex->fd_pipe) < 0)
		msg_error(ERR_PIPE, pipex);
	pipex->paths = find_path(envp);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	pipex->cmd = NULL;
	pipex->cmd_args = NULL;
}

void	ft_pipe(int ac ,char *av[], char *envp[])
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipex == NULL)
	{
		msg(ERR_MEMORY);
		exit(1);
	}
	struct_init(pipex, envp);
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		first_child(pipex, av, envp);
		close(pipex->fd_pipe[0]);
		close(pipex->fd_pipe[1]);
	}
	while (ac > 0)
	{
		pipex->pid2 = fork();
		if (ac == 1)
		{
			if (pipex->pid2 == 0)
			{
				last_child(pipex, av, envp);
			}
			close(pipex->fd_pipe[0]);
			close(pipex->fd_pipe[1]);
		}
		else
		{
			if (pipex->pid2 == 0)
			{
				middle_child(pipex, av, envp);
			}
			close(pipex->fd_pipe[0]);
			close(pipex->fd_pipe[1]);
		}
		waitpid(pipex->pid2, NULL, 0);
		ac--;
	}
	close_pipes(pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	child_free(pipex);
	parent_free(pipex);
	free(pipex);
}
