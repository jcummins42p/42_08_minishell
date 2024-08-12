/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:23:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/12 13:23:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_rdin(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
		pipex->fd_in = ft_open_file(token->token, O_RDONLY, 0);
}

void	ft_handle_rdout(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
		pipex->fd_out = ft_open_file(token->token,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_handle_app(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
		pipex->fd_out = ft_open_file(token->token,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}
