/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 15:05:56 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_mshell *msh, t_tokenlist *token)
{
	if (!token)
		return (1);
	else
	{
		if (token->comtype == C_EXIT)
			com_exit(msh, token);
		else if (token->comtype == C_ECHO)
			com_echo(msh, token);
		else if (token->comtype == C_ENV)
			com_env(&msh->envlist, ENVVAR);
		else if (token->comtype == C_UNSET)
			com_unset(msh);
		else if (token->comtype == C_EXPORT)
			com_export(msh, token, ENVVAR);
		else if (token->comtype == C_ASSIGN)
			com_export(msh, token, SHLVAR);
		else if (token->comtype == C_CD)
			com_cd(msh, token);
		else
			return (1);
	}
	return (0);
}
