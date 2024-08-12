/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:23:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/12 19:51:29 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_tokenlist *token)
{
	if (token->mtctype == RDIN
		|| token->mtctype == RDOUT
		|| token->mtctype == RDAPP
		|| token->mtctype == DELIMIT)
		return (true);
	else
		return (false);
}

void	do_redirection(t_mshell *msh, t_tokenlist *token)
{
	t_tokenlist	*curr;

	if (msh->info->n_rdin == 0 && msh->info->n_rdout == 0 &&
			msh->info->n_rdapp == 0 && msh->info->n_delimit == 0)
		return ;
	curr = token;
	while (curr)
	{
		if (is_redirect(curr))
			ft_handle_redirection(msh->pipex, curr);
		curr = curr->next;
	}
}

void	ft_handle_rdin(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
		pipex->fd_in = ft_open_file(token->expand, O_RDONLY, 0);
}

void	ft_handle_rdout(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
		pipex->fd_out = ft_open_file(token->expand,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_handle_app(t_pipex *pipex, t_tokenlist *token)
{
	token = token->next;
	if (token)
		pipex->fd_out = ft_open_file(token->expand,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}
