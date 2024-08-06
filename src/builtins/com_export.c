/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/06 17:33:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_var(t_mshell *msh, t_tokenlist *token, t_vscope scope)
{
	if (token->comtype == EXPORT)
		token = token->next;
	while (token && token->mtctype < PIPE)
	{
		if (token->mtctype)
			handle_exec_error(NULL, "command not found", token->expand);
		else
			env_from_str(&msh->envlist, token->expand, scope);
		token = token->next;
	}
	env_set_string(&msh->envlist, &msh->env);
}
