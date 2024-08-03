/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:33 by akretov           #+#    #+#             */
/*   Updated: 2024/08/03 19:01:26 by akretov          ###   ########.fr       */
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

//	exec_cmd
void	handle_exec_error(t_pipex *pipex, const char *error_message);
int		ft_open_file(const char *filename, int flags, mode_t mode);
void	ft_handle_redirection(t_pipex *pipex, t_tokenlist *tokens);
char	**ft_get_arg(t_pipex *pipex, t_tokenlist *tokens);
void	ft_exec_cmd(t_mshell *msh);


//	exec_pipe.c
void	child(t_pipex *pipex, char *env[]);
void	last_child(t_pipex *pipex, char *env[]);

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
