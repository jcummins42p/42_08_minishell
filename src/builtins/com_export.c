/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/14 16:03:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	com_export(t_mshell *msh, t_tokenlist *token, t_vscope scope)
{
	if (token->comtype == EXPORT)
		token = token->next;
	else if (token->comtype)
		handle_exec_error(NULL, "command not found", token->expand);
	while (token && token->mtctype < PIPE)
	{
		env_from_tokens(&msh->envlist, &token, scope);
		token = token->next;
		while (token && !token->prev->trail_space)
			token = token->next;
	}
	env_set_string(&msh->envlist, &msh->env);
	msh->exitcode = 0;
}
