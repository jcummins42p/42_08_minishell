/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:46:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/13 16:46:21 by jcummins         ###   ########.fr       */
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
			printf("%s", token->expand);
			if (token->trail_space && token->next && token->next->mtctype != PIPE)
				printf(" ");
			else if (newline && (!token->next || (token->next && token->next->mtctype == PIPE)))
				printf("\n");
			token = token->next;
		}
	}
}
