/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/31 19:22:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_cleanup(t_mshell *msh)
{
	token_clear(&msh->tokens);
	free(msh->lineread);
	msh->lineread = NULL;
}

int	input_execute(t_mshell *msh)
{
	t_tokenlist	*token;

	token = msh->tokens;
	if (msh->tokens)
	{
		if (token->comtype == EXIT)
			msh->running = false;
		else if (token->comtype == ECHO)
			echo_tokens(msh, 1);
		else if (token->comtype == ENV)
			env_print(&msh->envlist);
		else if (token->comtype == UNSET)
			unset(msh);
		else if (token->comtype == EXPORT)
			export_var(msh);
		else if (token->comtype == ASSIGN)
			export_var(msh);
		else if (token->comtype == CD)
			change_dir(msh, token->next->token);
		else
			ft_exec_init(msh);
	}
	return (0);
}

void	input_cycle(t_mshell *msh)
{
	while (msh->running)
	{
		msh->lineread = readline(*msh->prompt);
		add_history(msh->lineread);
		tokenize(msh);
		tokens_print(&msh->tokens);
		token_get_info(msh);
		if (input_execute(msh))
			break ;
		input_cleanup(msh);
	}
}
