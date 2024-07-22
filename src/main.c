/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/22 13:18:19 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	input_read(t_envlist *envlist, t_tokenlist *tokens, char *ptr)
{
	if (tokens)
		tokens_print(&tokens);
	if (!strncmp(ptr, "EXIT", 4))
		return (1);
	else if (!strncmp(ptr, "PRINT", 4))
		printf("%s\n", ptr);
	else if (!strncmp(ptr, "env", 3))
		env_print(&envlist);
	return (0);
}

void	input_cycle(t_mshell *msh, char *env[])         // delete env
{
	msh->prompt = *env_get(&msh->envlist, "SHELL");
	while (1)
	{
		msh->ptr = readline(msh->prompt);
		add_history(msh->ptr);
		tokenize(&msh->tokens, msh->ptr);
		if (input_read(msh->envlist, msh->tokens, msh->ptr) == 1)
			break ;
		
		//Pipe in progress
		if (ft_strrchr(msh->ptr, '|'))
			ft_pipe_init(msh->tokens, msh->ptr, env);

		token_clear(&msh->tokens);
		free(msh->ptr);
		msh->ptr = NULL;
	}
}

void	shell_init(t_mshell *msh)
{
	msh->envlist = NULL;
	msh->tokens = NULL;
	msh->ptr = NULL;
	msh->prompt = NULL;
}

void	shell_free(t_mshell *msh)
{
	if (msh->tokens)
		token_clear(&msh->tokens);
	env_clear(&msh->envlist);
	if (msh->ptr)
		free(msh->ptr);
}

int	main(int argc, char *argv[], char *env[])
{
	t_mshell	msh;
	char		*param = "$PATH";

	(void)argv;
	(void)argc;
	shell_init(&msh);
	env_init(&msh.envlist, env);
	expand_variable(&msh.envlist, param + 1);
	input_cycle(&msh, env); // delete env
	shell_free(&msh);
	return (0);
}
