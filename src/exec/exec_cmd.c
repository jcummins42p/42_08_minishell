/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/08/04 18:08:35 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_redirection(t_pipex *pipex, t_tokenlist **tokens)
{
	if ((*tokens)->mtctype == RDIN)
	{
		*tokens = (*tokens)->next;
		pipex->fd_in = ft_open_file((*tokens)->token, O_RDONLY, 0);
	}
	else if ((*tokens)->mtctype == RDOUT)
	{
		*tokens = (*tokens)->next;
		pipex->fd_out = ft_open_file((*tokens)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if ((*tokens)->mtctype == RDAPP)
	{
		*tokens = (*tokens)->next;
		pipex->fd_out = ft_open_file((*tokens)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	*tokens = (*tokens)->next;
}

char	**ft_get_arg(t_pipex *pipex, t_tokenlist **tokens)
{
	char		**arg;
	int			i;
	t_tokenlist	*ptr;

	ptr = *tokens;
	i = 0;
	if ((*tokens)->mtctype == PIPE)
	{
		*tokens = (*tokens)->next;
		ptr = ptr->next;
	}
	i = count_args(ptr);
	arg = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arg)
	{
		write(STDERR_FILENO, "Memory allocation failed\n", 25);
		return (NULL);
	}
	populate_args(pipex, tokens, arg);
	return (arg);
}

void	fork_and_execute(t_pipex *pipex, t_mshell *msh, int j, int n_pipes)
{
	pipex->pid[j] = fork();
	if (pipex->pid[j] < 0)
		handle_exec_error(pipex, "Fork error\n");
	if (pipex->pid[j] == 0)
	{
		if (j == n_pipes)
			last_child(pipex, msh->env, n_pipes);
		else
			child(pipex, msh->env);
	}
}

void execute_commands(t_mshell *msh, t_pipex *pipex, int n_pipes)
{
	int j;

	j = 0;
	while (j < n_pipes + 1)
	{
		pipex->cmd_args = ft_get_arg(pipex, &msh->tokens);
		if (!pipex->cmd_args)
			handle_exec_error(pipex, "Failed to get command arguments\n");

		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		if (!pipex->cmd)
			handle_exec_error(pipex, "Command not found\n");

		if ( n_pipes != 0)
		{
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, "Pipe creation error\n");
		}
		fork_and_execute(pipex, msh, j, n_pipes);
		if (j < n_pipes)
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
	execute_commands(msh, pipex, msh->info->n_pipe);
	cleanup(pipex, msh->info->n_pipe);
}
