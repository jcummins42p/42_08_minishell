/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/14 12:13:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_one_token_no_pipe(t_mshell *msh, t_tokenlist *token, bool newline)
{
	write(msh->pipex->fd_out, token->expand, strlen(token->expand));
	if (token->trail_space && token->next)
		write(msh->pipex->fd_out, " ", 1);
	else if (newline && !token->next)
		write(msh->pipex->fd_out, "\n", 1);
}

void	echo_one_token(t_tokenlist *token, bool newline)
{
	printf("%s", token->expand);
	if (token->trail_space && token->next && token->next->mtctype != PIPE)
		printf(" ");
	else if (newline && (!token->next || (token->next->mtctype == PIPE)))
		printf("\n");
}

void	echo_tokens_cycle(t_mshell *msh, t_tokenlist *token, bool newline)
{
	while (token && token->mtctype != PIPE)
	{
		if (is_redirect(token))
		{
			if (!token->next->next)
				return ;
			token = token->next->next;
		}
		else
		{
			if (msh->info->n_pipe == 0)
				echo_one_token_no_pipe(msh, token, newline);
			else
				echo_one_token(token, newline);
			token = token->next;
		}
	}
}

void	echo_tokens(t_mshell *msh, t_tokenlist *token)
{
	bool		newline;

	newline = true;
	if (token->next)
		token = token->next;
	if (!ft_strncmp(token->expand, "-n", 2))
	{
		token = token->next;
		newline = false;
	}
	echo_tokens_cycle(msh, token, newline);
	msh->exitcode = 0;
}
