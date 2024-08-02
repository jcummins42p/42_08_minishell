/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:57:22 by akretov           #+#    #+#             */
/*   Updated: 2024/08/02 16:07:47 by jcummins         ###   ########.fr       */
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

char **ft_get_arg_pipe(t_mshell *msh)
{
	t_tokenlist	*tokens;
	char		**arg;
	char		*new_arg;
	int			i;

	i = 0;
	tokens = msh->tokens;
	arg = NULL;
	arg = (char **)malloc(sizeof(int *) * msh->info->n_pipe + 1);
	arg[i] = ft_strdup("");
	if (!arg[i])
		return (NULL);
	while (tokens != NULL)
	{
		if (tokens->mtctype != PIPE)
		{
			/*new_arg = ft_strjoin(arg[i], tokens->expand);*/
			if (tokens->token[0] == '$')
				new_arg = ft_strjoin(arg[i], tokens->envvar->value);
			else if (tokens->var)
				new_arg = ft_strjoin(arg[i], tokens->var);
			else
				new_arg = ft_strjoin(arg[i], tokens->token);
			if (tokens->trail_space)
				new_arg = ft_strjoin(new_arg, " ");
			if (!new_arg)
			{
				// free everything in arg + new arg
				return (NULL);
			}
			free(arg[i]);
			arg[i] = new_arg;
		}
		else if (tokens->next != NULL)
		{
			i++;
			arg[i] = ft_strdup("");
			if (!arg[i])
			{
				// free everything in arg + new arg
				return (NULL);
			}
		}
		tokens = tokens->next;
	}
	arg[i + 1] = NULL;
	return (arg);
}

void child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[0]); // Close unused read end
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdin\n");
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdout\n");
	close(pipex->fd_pipe[1]); // Close the copy of write end
	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, "Execve failed\n");
}

void last_child(t_pipex *pipex, char *env[])
{
	close(pipex->fd_pipe[1]); // Close the unused write end

	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdin\n");
	close(pipex->fd_pipe[0]); // Close the unused read end

	// Last child outputs to the specified output or terminal
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		handle_exec_error(pipex, "Error duplicating file descriptor for stdout\n");
	if (execve(pipex->cmd, pipex->cmd_args, env) < 0)
		handle_exec_error(pipex, "Execve failed\n");
}

void ft_pipe(t_mshell *msh)
{
	t_pipex	*pipex;
	char	**av;
	int		i;
	int		j;

	pipex = msh->pipex;
	av = ft_get_arg_pipe(msh);
	i = msh->info->n_pipe + 1;
	j = 0;

	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * i);
	if (!pipex->pid)
	{
		msg("Memory allocation error");
		return;
	}
	pipex->fd_in = dup(STDIN_FILENO); // Start reading from stdin initially
	/*pipex->fd_out = open("text.txt", O_RDWR); // Save original stdout*/
	/*while (get_next_line(pipex->fd_out))	//	This to append >>*/
		/*;*/
	/*printf("File descriptor %d", pipex->fd_out);*/
	pipex->fd_out = dup(STDOUT_FILENO); // Save original stdout
	while (j < i)
	{
		pipex->cmd_args = ft_split(av[j], ' ');
		if (!pipex->cmd_args) {
			msg("Command split error\n");
			free_pipex(pipex);
			return;
		}
		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
		if (!pipex->cmd) {
			if (!exec_builtin(msh, msh->tokens))
				msg("Command not found\n");
			/*free_pipex(pipex);*/
			/*return;*/
		}
		if (j < i - 1) { // For all commands except the last one
			if (pipe(pipex->fd_pipe) < 0)
				handle_exec_error(pipex, "Pipe creation error\n");
		}

		pipex->pid[j] = fork();
		if (pipex->pid[j] < 0) {
			handle_exec_error(pipex, "Fork error\n");
		}

		if (pipex->pid[j] == 0)
		{ // Child process
			if (j == i - 1) { // Last command
				last_child(pipex, msh->env);
			} else {
				child(pipex, msh->env);
			}
		}
	// Parent process: Close write end and update fd_in for next child
		close(pipex->fd_pipe[1]);
		close(pipex->fd_in);

	// For the next command, fd_in becomes the read end of the current pipe
		if (j < i - 1)
			pipex->fd_in = pipex->fd_pipe[0];
		j++;
	}
	// Wait for all child processes to complete
	for (int k = 0; k < msh->info->n_pipe + 1; k++)
		waitpid(pipex->pid[k], NULL, 0);

	close(pipex->fd_in);
	close(pipex->fd_out);
	free_pipex(pipex);
}
