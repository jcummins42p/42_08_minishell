/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:12:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/30 13:32:56 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_mshell *msh)
{
	t_tokenlist	*token;

	token = msh->tokens;
	if (token->next)
		token = token->next;
	while (token && token->mtctype != PIPE)
	{
		env_unset(&msh->envlist, token->token);
		token = token->next;
	}
	env_set_string(&msh->envlist, &msh->env);
}
