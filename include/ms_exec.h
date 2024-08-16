/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/08/16 14:59:47 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H

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

//	exec_args.c
void	populate_args(t_pipex *pipex, t_tokenlist **tokens, char **arg[]);
int		count_args(t_tokenlist *tokens);
char	**ft_get_arg(t_pipex *pipex, t_tokenlist **tokens);
char	*get_cmd(char **paths, char *cmd);

//	exec_child_pr.c
void	child(t_pipex *pipex, t_mshell *msh, int curr_pipe);
void	last_child(t_pipex *pipex, t_mshell *msh, int n_pipes);

//	exec_cmd.c
void	ft_exec_cmd(t_mshell *msh);

//	exec_err.c			RE-WORK!
int		msg(const char *err);
void	msg_error(char *err, t_pipex *pipex);
void	handle_exec_error(t_pipex *pipex, char *str, char *arg);

//	exec_init.c
int		init_command_args(t_pipex *pipex, t_tokenlist *curr);
int		init_pid(t_pipex *pipex, int n_pipes);
void	init_pipex(t_mshell *msh);

//	exec_free.c
void	close_curr_fd(t_pipex *pipex);
void	free_cmd_paths(t_pipex *pipex);
void	free_cmd_args(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);

#endif
