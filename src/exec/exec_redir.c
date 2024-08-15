/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:23:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/15 11:58:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_tokenlist *token)
{
	if (token->mtctype >= RDIN)
		return (true);
	else
		return (false);
}

int	do_redirection(t_mshell *msh, t_tokenlist *token)
{
	t_tokenlist	*curr;


	if (msh->info->n_rdin == 0
		&& msh->info->n_rdout == 0
		&& msh->info->n_rdapp == 0
		&& msh->info->n_delimit == 0)
		return (0);
	curr = token;
	while (curr && curr->mtctype != PIPE)
	{
		if (is_redirect(curr))
			if (ft_handle_redirection(msh->pipex, curr) == 1)
				return (1);
		curr = curr->next;
	}
	return (0);
}

int	ft_handle_rdin(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token && token->expand)
	{
		if (pipex->fd_in)
			close(pipex->fd_in);
		pipex->fd_in = ft_open_file(token->expand, O_RDONLY, 0);
		if (pipex->fd_in == -1)
		{
			handle_exec_error(pipex, "No such file or dir", token->expand);
			return (1);
		}
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	else
	{
		// if it's already checked in parsing then it's not needed
		handle_exec_error(pipex, "Syntax error: missing file after '<'", "");
		return (1);
	}
	return (0);
}

void	ft_handle_rdout(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
	{
		if (pipex->fd_out)
			close(pipex->fd_out);
		pipex->fd_out = ft_open_file(token->expand,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		/*if (pipex->fd_out == -1)*/
		/*{*/
			/*handle_exec_error(pipex, "No such file or dir", token->expand);*/
		/*}*/
		/*dup2(pipex->fd_out, STDOUT_FILENO);*/
		/*close(pipex->fd_out);*/
	}
}

void	ft_handle_app(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
	{
		if (pipex->fd_out)
			close(pipex->fd_out);
		pipex->fd_out = ft_open_file(token->expand,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}
