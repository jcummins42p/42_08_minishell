/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/07/31 18:23:47 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_args_fill(int num_pipes, int *pipe_pos, char **pipe_arg[], char *ptr)
{
	int start = 0;
	int	i;

	start = 0;
	i = 0;
	while (i <= num_pipes)
	{
		int length = pipe_pos[i] - start;
		(*pipe_arg)[i] = (char *)malloc(sizeof(char) * (length + 1));
		ft_strlcpy((*pipe_arg)[i], ptr + start, length + 1);
		start = pipe_pos[i] + 1; // Move start to character after '|'
		i++;
	}
}

void	struct_init(t_mshell *msh)
{
	if (msh->info->n_pipe == 0)
		msh->pipex->pid = malloc(sizeof(pid_t));
	else
		msh->pipex->pid = malloc(sizeof(pid_t) * msh->info->n_pipe);
	msh->pipex->fd_in = -1;	//STDIN_FILENO
	msh->pipex->fd_out = -1;	//STDOUT_FILENO
	// Arguments for execve
	msh->pipex->paths = find_path(msh->envlist);
	msh->pipex->cmd_paths = ft_split(msh->pipex->paths, ':');
	msh->pipex->cmd = NULL;
	msh->pipex->cmd_args = NULL;
}

void	ft_exec_cmd(t_mshell *msh)
{
	t_pipex *pipex = msh->pipex;

	pipex->cmd_args = ft_split(msh->lineread, ' ');
	if (!pipex->cmd_args)
	{
		msg(ERR_MEMORY);
		exit(1);
	}
	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		msg(ERR_CMD);
		return ;
	}
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
	{
		msg(ERR_FORK);
		return ;
	}
	if (pipex->pid[0] == 0)
	{
		if (!execve(pipex->cmd, pipex->cmd_args, msh->env))
		{
			msg(ERR_EXEC);
			exit(1);
		}
	}
	//in the future setup signals
	if (waitpid(pipex->pid[0], NULL, 0) == -1)
	{
		msg(ERR_WAIT);
		return ;
	}
}

void	ft_exec_init(t_mshell *msh)
{
	msh->pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (msh->pipex == NULL)
	{
		msg(ERR_MEMORY);
		exit(1);
	}
	struct_init(msh);

	if (msh->info->n_pipe == 0)
	{
		ft_exec_cmd(msh);
		free_pipex(msh->pipex);
		return ;
	}
	else
	{
		ft_pipe(msh);
		// for (int i = 0; i < msh->info->n_pipe + 1; i++)
		// 	printf("Pipe arg%i is %s\n", i, pipe_arg[i]);
	}
}
