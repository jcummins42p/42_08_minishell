/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:32:29 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/12 14:40:06 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	default if no arg - to home dir
//	if next token is | then do not change dir even with
//	This only updates the environment variable OLDPWD - it does not give the
//	correct output using pwd command
void	change_dir(t_mshell *msh, t_tokenlist *token)
{
	/*(void)msh;*/
	/*(void)token;*/
	char	*curr_pwd;

	curr_pwd = NULL;
	curr_pwd = env_get_string(&msh->envlist, "PWD");
	env_set(&msh->envlist, "OLDPWD", curr_pwd, ENVVAR);
	if (token->next)
	{
		if (chdir(token->next->expand))
			printf("Invalid directory\n");	
	}
	/*if (token->next)*/
		/*token = token->next;*/
	/*else*/
	/*{*/
		/*// change directory to home*/
		/*return ;*/
	/*}*/

	/*env_set_string(&msh->envlist, &msh->env);*/
	//  at the beginning OLDPWD and PWD = getcwd;
	// PWD = cd;
	// CD = home if next token == NULL | next token == Pipe
}
