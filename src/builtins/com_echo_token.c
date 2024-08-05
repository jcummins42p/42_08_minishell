/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/05 16:33:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_one_token(t_tokenlist *token, int fd)
{
	/*if (token->envvar)*/
		/*ft_putstr_fd(token->envvar->value, fd);*/
	/*else if (token->mtctype == DOLLAR && (!token->envvar || *token->var == '\0'))*/
		/*return (0);*/
	/*else if (token->mtctype != DOLLAR && token->var && !token->envvar)*/
		/*ft_putstr_fd(token->var, fd);*/
	/*else*/
		ft_putstr_fd(token->expand, fd);
	return (1);
}

void	echo_tokens(t_mshell *msh, int fd)
{
	t_tokenlist	*token;
	bool		newline;

	newline = true;
	printf("Using builtin echo function\n");
	token = msh->tokens;
	if (token->next)
		token = token->next;
	while (token->next && token->mtctype >= PIPE)
	{
		if (ft_strncmp(token->expand, "-n", 2))
		{
			token = token->next;
			newline = false;
		}
		if (echo_one_token(token, fd) && token->trail_space)
			write(fd, " ", 1);
		token = token->next;
	}
	if (token && token->mtctype != PIPE)
	{
		echo_one_token(token, fd);
		if (!newline)
			write(fd, "\n", 1);
	}
}
