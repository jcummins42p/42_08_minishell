/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:14:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 12:34:47 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDIRECT_H
# define MS_REDIRECT_H

//	redir_handlers.c
int		ft_handle_rdin(t_pipex *pipex, t_tokenlist *token);
int		ft_handle_rdout(t_pipex *pipex, t_tokenlist *token);
int		ft_handle_app(t_pipex *pipex, t_tokenlist *token);
int		ft_handle_redirection(t_pipex *pipex, t_tokenlist *tokens);
int		do_redirection(t_mshell *msh, t_tokenlist *token);

//	redir_heredoc.c
void	ft_handle_heredoc(t_pipex *pipex, const char *delimiter);
int		ft_open_file(const char *filename, int flags, mode_t mode);

#endif
