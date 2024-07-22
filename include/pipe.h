/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/07/22 13:18:32 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include <sys/types.h>
#include <sys/wait.h>

# define ERR_INFILE "No such file or directory"
# define ERR_OUTFILE "No such file or directory"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_MEMORY "Not enough memory for struct"
# define ERR_EXEC "Execution didn't work"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_pipe[2];
	// int		fd_in;			// this is for re-direction - From 
	// int		fd_out;			// this is for re-direction - To
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

//pipe_0.c
void		ft_pipe_init(t_tokenlist *tokens, char *ptr, char *env[]);

//pipe_1.c
char		*find_path(char **envp);
void		struct_init(t_pipex *pipex, char *envp[]);
void		ft_pipe(int num_pipes ,char *pipe_arg[], char *env[]);

//pipe_utils.c
void		close_pipes(t_pipex *pipex);
int			msg(char *err);
void		msg_error(char *err, t_pipex *pipex);
void		parent_free(t_pipex *pipex);
void		child_free(t_pipex *pipex);

//pipe_child.c
char		*get_cmd(char **paths, char *cmd);
void		first_child(t_pipex *pipex, char *av[], char *envp[]);
void		middle_child(t_pipex *pipex, char *av[], char *envp[]);
void		last_child(t_pipex *pipex, char *av[], char *envp[]);

#endif
