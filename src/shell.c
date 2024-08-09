/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:32:23 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/09 14:33:20 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_free(t_mshell *msh)
{
	if (msh->tokens)
		token_clear(&msh->tokens);
	env_list_clear(&msh->envlist);
	env_string_clear(msh->env);
	if (msh->lineread)
		free(msh->lineread);
	free (msh->info);
}

void	shell_set_envptrs(t_mshell *msh)
{
	msh->prompt = env_get_value(&msh->envlist, "PS1");
	msh->path = env_get_value(&msh->envlist, "PATH");
}

void	shell_init(t_mshell *msh)
{
	msh->pipex = NULL;
	msh->tokens = NULL;
	msh->info = malloc(sizeof(t_token_inf));
	msh->envlist = NULL;
	msh->env = NULL;
	msh->prompt = NULL;
	msh->path = NULL;
	msh->lineread = NULL;
	msh->running = true;
	msh->exitcode = 0;
}
