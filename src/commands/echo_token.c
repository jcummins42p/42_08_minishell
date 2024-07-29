/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/29 15:22:21 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_one_token(t_tokenlist *token, int fd)
{
	if (token->envvar)
		ft_putstr_fd(token->envvar->value, fd);
	else if (token->mtctype == DOLLAR && !token->envvar)
		;
	else if (token->mtctype != DOLLAR && token->var && !token->envvar)
		ft_putstr_fd(token->var, fd);
	else
		ft_putstr_fd(token->token, fd);
}

void	echo_tokens(t_mshell *msh, int fd)
{
	t_tokenlist	*token;

	token = msh->tokens;
	if (token->next)
		token = token->next;
	while (token->next)
	{
		echo_one_token(token, fd);
		if (token->envvar && token->trail_space)
			write(fd, " ", 1);
		token = token->next;
	}
	if (token)
	{
		echo_one_token(token, fd);
		write(fd, "\n", 1);
	}
}
