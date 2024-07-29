/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/29 14:49:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_tokens(t_mshell *msh, int fd)
{
	t_tokenlist	*token;

	token = msh->tokens;
	if (token->next)
		token = token->next;
	while (token->next)
	{
		if (token->envvar)
			ft_putstr_fd(token->envvar->value, fd);
		else if (token->var)
			ft_putstr_fd(token->var, fd);
		else
			ft_putstr_fd(token->token, fd);
		if (token->envvar && token->trail_space)
			write(fd, " ", 1);
		token = token->next;
	}
	if (token)
	{
		if (token->envvar)
			ft_putstr_fd(token->envvar->value, fd);
		else if (token->var)
			ft_putstr_fd(token->var, fd);
		else
			ft_putstr_fd(token->token, fd);
		write(fd, "\n", 1);
	}
}
