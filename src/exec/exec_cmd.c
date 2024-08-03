/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/08/03 19:03:46 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec_error(t_pipex *pipex, const char *error_message)
{
	(void)pipex;
	/*free_pipex(pipex);*/
	msg(error_message);
	exit(1);
}


int	ft_open_file(const char *filename, int flags, mode_t mode)
{
	int fd = open(filename, flags, mode);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Couldn't open the file\n", 23);
	}
	return (fd);
}


void	ft_handle_redirection(t_pipex *pipex, t_tokenlist *tokens)
{
	if (tokens->mtctype == RDIN)
	{
		tokens = tokens->next;
		pipex->fd_in = ft_open_file(tokens->var, O_RDONLY, 0);
	}
	else if (tokens->mtctype == RDOUT)
	{
		tokens = tokens->next;
		pipex->fd_out = ft_open_file(tokens->var, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (tokens->mtctype == RDAPP)
	{
		tokens = tokens->next;
		pipex->fd_out = ft_open_file(tokens->var, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	tokens = tokens->next;
}

// Function to get arguments
char	**ft_get_arg(t_pipex *pipex, t_tokenlist *tokens)
{
	char		**arg;
	int			i;
	t_tokenlist	*ptr;

	// Count the number of arguments
	ptr = tokens;
	i = 0;
	while (ptr && ptr->mtctype != PIPE)
	{
		if (ptr->mtctype != RDIN && ptr->mtctype != RDOUT && ptr->mtctype != RDAPP)
		{
			i++;
		}
		ptr = ptr->next;
	}

	// Allocate memory for arguments array
	arg = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arg)
	{
		write(STDERR_FILENO, "Memory allocation failed\n", 25);
		return NULL;
	}

	// Populate the arguments array
	ptr = tokens;
	i = 0;
	while (ptr && ptr->mtctype != PIPE)
	{
		if (ptr->mtctype == RDIN || ptr->mtctype == RDOUT || ptr->mtctype == RDAPP)
		{
			ft_handle_redirection(pipex, tokens);
		}
		else
		{
			arg[i] = ptr->var;
			i++;
			ptr = ptr->next;
		}
	}
	arg[i] = NULL;

	return arg;
}

void	ft_exec_cmd(t_mshell *msh)
{
	t_pipex	*pipex;
	int		n_pipes;
	char	**arg;
	int		j;

	pipex = msh->pipex;
	n_pipes = msh->info->n_pipe;
	j = 0;
	arg = NULL;
	//If there is 1 builtin command without pipe then it should be executed by main program
	//Unique case
	if (n_pipes == 0 && !exec_builtin(msh, msh->tokens))
		return;
	else 
	{
		pipex->pid = (pid_t *)malloc(sizeof(pid_t) * (n_pipes + 1));
		if (!pipex->pid)
		{
			msg("Memory allocation error");
			return;
		}
		while (j < n_pipes)
		{
			pipex->cmd_args = ft_get_arg(pipex, msh->tokens);
			// add error handling for cmd_args
			for (int i = 0; pipex->cmd_args[i]; i++)
				printf("Is it working %s\n?", pipex->cmd_args[i]);
			
			pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
			// add error handling for cmd
			if (j < n_pipes - 1)
			{ // For all commands except the last one
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, "Pipe creation error\n");
			}
			pipex->pid[j] = fork();
		if (pipex->pid[j] < 0) {
			handle_exec_error(pipex, "Fork error\n");
		}

		if (pipex->pid[j] == 0)
		{ // Child process
			if (j == n_pipes - 1) { // Last command
				last_child(pipex, msh->env);
			} else {
				child(pipex, msh->env);
			}
		}
		// Parent process: Close write end and update fd_in for next child
		close(pipex->fd_pipe[1]);
		close(pipex->fd_in);

		// For the next command, fd_in becomes the read end of the current pipe
		if (j < n_pipes - 1)
			pipex->fd_in = pipex->fd_pipe[0];
		j++;
		}
		// ADD signals
		for (int k = 0; k < msh->info->n_pipe + 1; k++)
			waitpid(pipex->pid[k], NULL, 0);
		close(pipex->fd_in);
		close(pipex->fd_out);
		free_pipex(pipex);
	}
}
