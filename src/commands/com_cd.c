/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:32:29 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/30 18:10:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	default if no arg - to home dir
//	if next token is | then do not change dir even with
//	This only updates the environment variable OLDPWD - it does not give the
//	correct output using pwd command
void	change_dir(t_mshell *msh, char *newdir)
{
	env_set(&msh->envlist, "OLDPWD", newdir);
	env_set_string(&msh->envlist, &msh->env);
}
