/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/13 16:16:05 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_tokens(t_mshell *msh, t_tokenlist *token)
{
	bool		newline;
	t_tokenlist	*curr;

	newline = true;
	curr = token;
	(void)msh;
	if (token->next)
		token = token->next;
	if (!ft_strncmp(token->expand, "-n", 2))
	{
		token = token->next;
		newline = false;
	}
	// while (curr)
	// {
	// 	if (is_redirect(curr))
	// 		ft_handle_redirection(msh->pipex, &curr);
	// 	else
	// 		curr = curr->next;
	// }
	//to go through the string first in order to prepare fd_out
	while (token && token->next && token->mtctype != PIPE)
	{
		// skip all the redirection as it was check above
		if (is_redirect(token))
		{
			if (!token->next->next)
			return ;
			token = token->next->next;
		}
		else
		{
			printf("%s", token->expand);
			// ft_putstr_fd(token->expand, msh->pipex->fd_out);
			if (token->trail_space)
				printf(" ");
				// write(msh->pipex->fd_out, " ", 1);
			token = token->next;
		}
	}
	if (token && token->mtctype != PIPE && !is_redirect(token))
	{
		printf("%s", token->expand);
		// ft_putstr_fd(token->expand, msh->pipex->fd_out);
		if (newline)
			printf("\n");
			// ft_putstr_fd("\n", msh->pipex->fd_out);
	}
}
