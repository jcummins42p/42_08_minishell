/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/08/04 17:18:12 by akretov          ###   ########.fr       */
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

//	exec_cmd.c
void 		handle_exec_error(t_pipex *pipex, char *str);
void		ft_handle_redirection(t_pipex *pipex, t_tokenlist **tokens);
char		**ft_get_arg(t_pipex *pipex, t_tokenlist **tokens);
int 		count_args(t_tokenlist *tokens);
void 		populate_args(t_pipex *pipex, t_tokenlist **tokens, char **arg);
void		ft_exec_cmd(t_mshell *msh);
int			init_pid(t_pipex *pipex, int n_pipes);
void		execute_commands(t_mshell *msh, t_pipex *pipex, int n_pipes);
void		fork_and_execute(t_pipex *pipex, t_mshell *msh, int j, int n_pipes);
void		cleanup(t_pipex *pipex, int n_pipes);
int			ft_open_file(const char *filename, int flags, mode_t mode);


//	exec_pipe.c
void	child(t_pipex *pipex, char *env[]);
void 	last_child(t_pipex *pipex, char *env[], int n_pipes);

//	exec_utils.c
char		*find_path(t_envlist *env);
char		*get_cmd(char **paths, char *cmd);
void		free_pipex(t_pipex *pipex);

//	exec_init.c
void		pipex_init(t_mshell *msh);
void		ft_exec_init(t_mshell *msh);

//	not needed || will be replaced by universal msg_error
void		msg_error(char *err, t_pipex *pipex);
int			msg(const char *err);

#endif
