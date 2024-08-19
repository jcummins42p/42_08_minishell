/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:23:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 17:51:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_rdin(t_pipex *pipex, t_tokenlist *token)
{
	int	temp;

	token = token->next;
	if (token && token->expand)
	{
		temp = ft_open_file(token->expand, O_RDONLY, 0);
		if (temp == -1)
		{
			if (errno == EACCES)
				handle_exec_error(pipex, ERR_PERM, token->expand);
			else
				handle_exec_error(pipex, ERR_INFILE, token->expand);
			return (1);
		}
		close(pipex->fd_in);
		pipex->fd_in = dup(temp);
		close(temp);
	}
	return (0);
}

int	ft_handle_rdout(t_pipex *pipex, t_tokenlist *token)
{
	int		temp;
	char	*target_file;

	target_file = NULL;
	token = token->next;
	if (token)
	{
		target_file = strcat_from_tokens(token, PIPE);
		pipex->rd_flag = true;
		temp = ft_open_file(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (temp == -1)
		{
			if (errno == EACCES)
				handle_exec_error(pipex, ERR_PERM, target_file);
			else
				handle_exec_error(pipex, ERR_OUTFILE, target_file);
			free(target_file);
			return (1);
		}
		close(pipex->fd_out);
		pipex->fd_out = dup(temp);
		close(temp);
		free(target_file);
	}
	return (0);
}

int	ft_handle_app(t_pipex *pipex, t_tokenlist *token)
{
	int	temp;

	token = token->next;
	if (token)
	{
		pipex->rd_flag = true;
		temp = ft_open_file(token->expand, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (temp == -1)
		{
			if (errno == EACCES)
				handle_exec_error(pipex, ERR_PERM, token->expand);
			else
				handle_exec_error(pipex, ERR_OUTFILE, token->expand);
			return (1);
		}
		close(pipex->fd_out);
		pipex->fd_out = dup(temp);
		close(temp);
	}
	return (0);
}

int	ft_handle_redirection(t_pipex *pipex, t_tokenlist *tokens)
{
	if (tokens->mtctype == RDIN)
	{
		if (ft_handle_rdin(pipex, tokens) == 1)
			return (1);
	}
	else if (tokens->mtctype == RDOUT)
	{
		if (ft_handle_rdout(pipex, tokens) == 1)
			return (1);
	}
	else if (tokens->mtctype == RDAPP)
	{
		if (ft_handle_app(pipex, tokens) == 1)
			return (1);
	}
	else if (tokens->mtctype == DELIMIT)
	{
		tokens = tokens->next;
		if (tokens)
			ft_handle_heredoc(pipex, tokens->token);
	}
	if (tokens)
		tokens = tokens->next;
	return (0);
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
		if (curr->mtctype >= RDIN)
			if (ft_handle_redirection(msh->pipex, curr) == 1)
			{
				msh->exitcode = 1;
				return (1);
			}
		curr = curr->next;
	}
	return (0);
}
