/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:32:29 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 17:04:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	default if no arg - to home dir
//	if next token is | then do not change dir even with
//	This only updates the environment variable OLDPWD - it does not give the
//	correct output using pwd command

void	com_cd_home(t_mshell *msh, t_tokenlist *token)
{
	char	*prefix;
	char	*suffix;
	char	*final;

	prefix = NULL;
	prefix = env_get_string(&msh->envlist, "HOME");
	suffix = NULL;
	final = NULL;
	if (token->next)
	{
		token = token->next;
		suffix = ft_substr(token->expand, 1, ft_strlen(token->expand) - 1);
		final = ft_strjoin(prefix, suffix);
	}
	else
		final = ft_strdup(prefix);
	if (chdir(final))
		write(2, "Invalid directory\n", 18);
	free(prefix);
	free(suffix);
	free(final);
}

void	com_cd(t_mshell *msh, t_tokenlist *token)
{
	char	*tmp_dir;
	char	buff[2048];

	tmp_dir = NULL;
	tmp_dir = env_get_string(&msh->envlist, "PWD");
	env_set(&msh->envlist, "OLDPWD", tmp_dir, ENVVAR);
	free (tmp_dir);
	if (token->next && ft_strncmp(token->next->expand, "~", 1))
	{
		if (chdir(token->next->expand))
			write(2, "Invalid directory\n", 18);
	}
	else
	{
		com_cd_home(msh, token);
	}
	tmp_dir = NULL;
	env_set(&msh->envlist, "PWD", getcwd(buff, 2048), ENVVAR);
}
