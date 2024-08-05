/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/05 19:53:10 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_tokens(t_mshell *msh, int fd)
{
	t_tokenlist	*token;
	bool		newline;

	newline = true;
	token = msh->tokens;
	if (token->next)
		token = token->next;
	if (!ft_strncmp(token->expand, "-n", 2))
	{
		token = token->next;
		newline = false;
	}
	while (token && token->next && token->mtctype < PIPE)
	{
		ft_putstr_fd(token->expand, fd);
		if (token->trail_space)
			write(fd, " ", 1);
		token = token->next;
	}
	if (token && token->mtctype != PIPE)
	{
		ft_putstr_fd(token->expand, fd);
		if (newline)
			write(fd, "\n", 1);
	}
}
