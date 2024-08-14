/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/08/14 13:27:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PIPE_H
# define MS_PIPE_H

# include <sys/types.h>
# include <sys/wait.h>

# define ERR_INFILE "No such file or directory\n"
# define ERR_OUTFILE "No such file or directory\n"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe wasn't created\n"
# define ERR_CMD "Command not found\n"
# define ERR_MEMORY "Not enough memory for struct\n"
# define ERR_EXEC "Execution didn't work\n"
# define ERR_FORK "Fork wasnt created\n"
# define ERR_WAIT "Something happened with child process\n"
# define ERR_STDIN "Error duplicating file descriptor for stdin\n"
# define ERR_STDOUT "Error duplicating file descriptor for stdout\n"

//	exec_child_pr.c
void	child(t_pipex *pipex, t_mshell *msh, int curr_pipe);
void	last_child(t_pipex *pipex, t_mshell *msh, int n_pipes);

//	exec_cmd.c
void	fork_and_execute(t_pipex *pipex, t_mshell *msh, int j);
int		execute_commands(t_mshell *msh, t_pipex *pipex, int j);
void	ft_exec_cmd(t_mshell *msh);

//	exec_redir.c
bool	is_redirect(t_tokenlist *token);
int		do_redirection(t_mshell *msh, t_tokenlist *token);
int		ft_handle_rdin(t_pipex *pipex, t_tokenlist *token);
void	ft_handle_rdout(t_pipex *pipex, t_tokenlist *token);
void	ft_handle_app(t_pipex *pipex, t_tokenlist *token);

//	exec_file_d.c
int		ft_handle_redirection(t_pipex *pipex, t_tokenlist *tokens);
int		ft_open_file(const char *filename, int flags, mode_t mode);

//	exec_init.c
int		init_pid(t_pipex *pipex, int n_pipes);
void	pipex_init(t_mshell *msh);
void	ft_exec_init(t_mshell *msh);

//	exec_utils_args.c
void	populate_args(t_pipex *pipex, t_tokenlist **tokens, char **arg[]);
int		count_args(t_tokenlist *tokens);
char	**ft_get_arg(t_pipex *pipex, t_tokenlist **tokens);
char	*get_cmd(char **paths, char *cmd);

//	exec_utils_err.c			RE-WORK!
int		msg(const char *err);
void	msg_error(char *err, t_pipex *pipex);
void	handle_exec_error(t_pipex *pipex, char *str, char *arg);

//	exec_utils_free.c			Currently issue with free
void	execute_cleanup(t_pipex *pipex);
void	cleanup(t_mshell *msh, t_pipex *pipex, int n_pipes);
void	free_pipex(t_pipex *pipex);

#endif
