/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 17:41:19 by jcummins         ###   ########.fr       */
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

void	input_cycle(t_mshell *msh)
{
	msh->ptr = NULL;
	msh->tokens = NULL;
	while (1)
	{
		msh->prompt = env_get(&msh->envlist, "SHELL");
		msh->ptr = readline(msh->prompt);
		add_history(msh->ptr);
		tokenize(&msh->tokens, msh->ptr);
		if (input_read(msh->envlist, msh->tokens, msh->ptr) == 1)
			break ;
		token_clear(&msh->tokens);
		free(msh->ptr);
		free(msh->prompt);
		msh->ptr = NULL;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_mshell	msh;

	(void)argv;
	(void)argc;
	msh.envlist = NULL;
	msh.tokens = NULL;
	env_init(&msh.envlist, env);
	input_cycle(&msh);
	env_clear(&msh.envlist);
	return (0);
}
