/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:32:29 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/12 18:32:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	default if no arg - to home dir
//	if next token is | then do not change dir even with
//	This only updates the environment variable OLDPWD - it does not give the
//	correct output using pwd command
void	change_dir(t_mshell *msh, t_tokenlist *token)
{
	char	*tmp_dir;
	char	buff[2048];

	tmp_dir = NULL;
	tmp_dir = env_get_string(&msh->envlist, "PWD");
	env_set(&msh->envlist, "OLDPWD", tmp_dir, ENVVAR);
	free (tmp_dir);
	if (token->next && ft_strncmp(token->next->expand, "~/", 2))
	{
		if (chdir(token->next->expand))
			printf("Invalid directory\n");
	}
	else
	{
		tmp_dir	= env_get_string(&msh->envlist, "HOME");
		if (chdir(tmp_dir))
			printf("Invalid directory\n");
		free (tmp_dir);
	}
	tmp_dir = NULL;
	env_set(&msh->envlist, "PWD", getcwd(buff, 2048), ENVVAR);
}
