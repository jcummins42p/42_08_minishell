/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/09 18:17:16 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_tokens(t_mshell *msh, t_tokenlist *token)
{
	bool		newline;
	t_tokenlist	*cur;

	newline = true;
	cur = token;
	if (token->next)
		token = token->next;
	if (!ft_strncmp(token->expand, "-n", 2))
	{
		token = token->next;
		newline = false;
	}
	//to go through the string first in order to prepare fd_out
	while (cur)
	{
		if (token->mtctype == RDIN
			|| token->mtctype == RDOUT
			|| token->mtctype == RDAPP)
			ft_handle_redirection(msh->pipex, &cur);
		else
			cur = cur->next;
	}
	while (token && token->mtctype != PIPE)
	{
		// skip all the redirection as it was check above
		if (token->mtctype == RDIN
			|| token->mtctype == RDOUT
			|| token->mtctype == RDAPP)
			token = token->next->next;
		else
		{
			ft_putstr_fd(token->expand, msh->pipex->fd_out);
			if (token->trail_space)
				write(msh->pipex->fd_out, " ", 1);
			token = token->next;
		}
	}
	if (token && token->mtctype != PIPE
		&& token->mtctype != RDIN
			&& token->mtctype != RDOUT
			&& token->mtctype != RDAPP)
	{
		ft_putstr_fd(token->expand, msh->pipex->fd_out);
		if (newline)
			write(msh->pipex->fd_out, "\n", 1);
	}
}
