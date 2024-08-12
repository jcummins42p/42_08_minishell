/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/12 17:38:50 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_redirection(t_tokenlist **token)
{
	if (!(*token)->next->next)
		return (1);
	*(*token) = *(*token)->next->next;
	return (0);
}

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

void do_redirection(t_mshell *msh, t_tokenlist *token)
{
	t_tokenlist	*curr;

	curr = token;
	while (curr)
	{
		if (is_redirect(curr))
			ft_handle_redirection(msh->pipex, &curr);
		else
			curr = curr->next;
	}
}

void	echo_tokens(t_mshell *msh, t_tokenlist *token)
{
	bool		newline;
	t_tokenlist	*curr;

	newline = true;
	curr = token;
	if (token->next)
		token = token->next;
	if (!ft_strncmp(token->expand, "-n", 2))
	{
		token = token->next;
		newline = false;
	}
	do_redirection(msh, token);
	//to go through the string first in order to prepare fd_out
	while (token && token->next && token->mtctype != PIPE)
	{
		// skip all the redirection as it was check above
		if (is_redirect(token))
		{
			if (skip_redirection(&token))
				return ;
		}
		else
		{
			ft_putstr_fd(token->expand, msh->pipex->fd_out);
			if (token->trail_space)
				write(msh->pipex->fd_out, " ", 1);
			token = token->next;
		}
	}
	if (token && token->mtctype != PIPE && !is_redirect(token))
	{
		ft_putstr_fd(token->expand, msh->pipex->fd_out);
		if (newline)
			ft_putstr_fd("\n", msh->pipex->fd_out);
	}
}
