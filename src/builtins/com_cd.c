/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:32:29 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/10 19:06:33 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	default if no arg - to home dir
//	if next token is | then do not change dir even with
//	This only updates the environment variable OLDPWD - it does not give the
//	correct output using pwd command
void	change_dir(t_mshell *msh, char *newdir)
{
	env_set(&msh->envlist, "OLDPWD", newdir, ENVVAR);
	env_set_string(&msh->envlist, &msh->env);
	//  at the beginning OLDPWD and PWD = getcwd;
	// PWD = cd;
	// CD = home if next token == NULL | next token == Pipe
}
