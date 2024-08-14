/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:13:33 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/14 15:14:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_update_exitcode(t_mshell *msh, t_envlist **envlist)
{
	char	*exitcode;

	exitcode = ft_itoa(msh->exitcode);
	env_set(envlist, "?", exitcode, SHLVAR);
	free(exitcode);
}
