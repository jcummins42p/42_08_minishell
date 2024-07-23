/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 17:17:40 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (!strncmp(ptr, "env", 3))
		env_print(&envlist);
	return (0);
}

void	input_cycle(t_mshell *msh, char *env[])
{
	(void)env;
	msh->prompt = *env_get_val(&msh->envlist, "SHELL");
	while (1)
	{
		msh->lineread = readline(msh->prompt);
		add_history(msh->lineread);
		tokenize(msh);
		if (input_read(msh->envlist, msh->tokens, msh->lineread))
			break ;
		//Execute command
		// if (ft_strrchr(msh->ptr, '|') || msh->tokens->next == NULL)
		/*ft_exec_init(msh->tokens, msh->lineread, env);*/
		tokens_print(&msh->tokens);
		token_clear(&msh->tokens);
		free(msh->lineread);
		msh->lineread = NULL;
	}
}

void	shell_init(t_mshell *msh)
{
	msh->envlist = NULL;
	msh->tokens = NULL;
	msh->lineread = NULL;
	msh->prompt = NULL;
}

void	shell_free(t_mshell *msh)
{
	if (msh->tokens)
		token_clear(&msh->tokens);
	env_clear(&msh->envlist);
	if (msh->lineread)
		free(msh->lineread);
}

int	main(int argc, char *argv[], char *env[])
{
	t_mshell	msh;
	/*char		*param = "$PATH";*/

	(void)argv;
	(void)argc;
	shell_init(&msh);
	env_init(&msh.envlist, env);
	/*expand_variable(&msh.envlist, param + 1);*/
	input_cycle(&msh, env);
	shell_free(&msh);	// env is freed in shell_free:env_clear
	return (0);
}
