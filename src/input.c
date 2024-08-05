/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/05 19:34:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_cleanup(t_mshell *msh)
{
	token_clear(&msh->tokens);
	free(msh->lineread);
	msh->lineread = NULL;
}

int	exec_builtin(t_mshell *msh, t_tokenlist *token, int fd)
{
	if (!token)
		return (1);
	else
	{
		if (token->comtype == EXIT)
			msh->running = false;
		else if (token->comtype == ECHO)
			echo_tokens(msh, fd);
		else if (token->comtype == ENV)
			env_print(&msh->envlist, ENVVAR);
		else if (token->comtype == UNSET)
			unset(msh);
		else if (token->comtype == EXPORT)
			export_var(msh, ENVVAR);
		else if (token->comtype == ASSIGN)
			export_var(msh, SHLVAR);
		else if (token->comtype == CD)
			change_dir(msh, token->next->token);
		else
			return (1);
	}
	return (0);
}

void	input_cycle(t_mshell *msh)
{
	while (msh->running)
	{
		msh->lineread = readline(*msh->prompt);
		add_history(msh->lineread);
		if (tokenize(msh))
		{
			tokens_get_info(msh);
			if (msh->tokens)
			{
				if (msh->tokens->comtype == EXIT)
					msh->running = false;
				else
					ft_exec_init(msh);
			}
		}
		input_cleanup(msh);
	}
}
