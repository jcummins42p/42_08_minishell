/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/07/23 17:42:49 by akretov          ###   ########.fr       */
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
		// (*pipe_arg)[i][length] = '\0';
		start = pipe_pos[i] + 1; // Move start to character after '|'
		i++;
	}
}

void	struct_init(t_pipex *pipex, char *envp[], int num_pipes)
{
	if (num_pipes == 0)
		pipex->pid = (pid_t *)malloc(sizeof(pid_t));
	else
		pipex->pid = (pid_t *)malloc(sizeof(pid_t) * num_pipes);
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	// Arguments for execve
	pipex->paths = find_path(envp);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	pipex->cmd = NULL;
	pipex->cmd_args = NULL;
}

void	ft_exec_cmd(t_pipex *pipex, char *av, char **env)
{
	pipex->cmd_args = ft_split(av, ' ');
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
		if (!execve(pipex->cmd, pipex->cmd_args, env))
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

void	ft_exec_init(t_tokenlist *tokens, char *ptr, char *env[])
{
	char	**pipe_arg;
	int		*pipe_pos;
	int		num_pipes;
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipex == NULL)
	{
		msg(ERR_MEMORY);
		exit(1);
	}
	pipe_pos = NULL;
	pipe_arg = NULL;
	num_pipes = token_count_type(&tokens, "|");
	struct_init(pipex, env, num_pipes);

	if (num_pipes == 0)
	{
		ft_exec_cmd(pipex, ptr, env);
		free_pipex(pipex);
		return ;
	}
	else
	{
		//prepare arguments for pipe
		pipe_pos = (int *)malloc(sizeof(int) * (num_pipes + 1));		  // +1 because for input test | arg   we have 2 arguments test and arg.
		pipe_arg = (char **)malloc(sizeof(char *) * (num_pipes + 1 + 1)); // +1 for NULL termination

		token_pos_type(&tokens, &pipe_pos, "|");

		// Get pipe positions
		// Get end of the line positions           || the re-direction
		pipe_pos[num_pipes] = ft_strlen(ptr);
		pipe_arg[num_pipes + 1] = NULL;
		pipe_args_fill(num_pipes, pipe_pos, &pipe_arg, ptr);
		
		
		// printf("Number of pipes %i\n", num_pipes);
		for (int i = 0; i < num_pipes+1; i++)
		printf("pipe arg:%s\n", pipe_arg[i]);
		ft_pipe(num_pipes, pipe_arg, env, pipex);
	}

	
	free(pipe_pos);	
	for (int i = 0; i <= num_pipes; i++)
		free(pipe_arg[i]);
	free(pipe_arg);
}
