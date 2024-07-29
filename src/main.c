/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/29 13:55:46 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_read(t_mshell *msh)
{
	if (msh->tokens)
		tokens_print(&msh->tokens);
	if (!ft_strncmp(msh->lineread, "exit", 4))
		return (1);
	else if (!ft_strncmp(msh->lineread, "echo", 4))
		echo_tokens(msh, 1);
		/*echo_expand_str(msh, msh->lineread, 1);*/
	else if (!ft_strncmp(msh->lineread, "env", 3))
		env_print(&msh->envlist);
	else
		ft_exec_init(msh->tokens, msh->lineread, msh->env);
	return (0);
}

void	input_cleanup(t_mshell *msh)
{
	token_clear(&msh->tokens);
	free(msh->lineread);
	msh->lineread = NULL;
}

void	input_cycle(t_mshell *msh)
{
	/*env_set(&msh->envlist, "PS1", "Hello: ");*/
	/*printf("path variable is %s\n", *msh->path);*/
	/*env_set(&msh->envlist, "PATH", ";shdflkshdfklghadkfhgsdh");*/
	/*printf("path variable is %s\n", *msh->path);*/
	while (1)
	{
		msh->lineread = readline(*msh->prompt);
		add_history(msh->lineread);
		tokenize(msh);
		token_get_info(msh);
		if (input_read(msh))
			 break ;
		input_cleanup(msh);
	}
}

void	shell_init(t_mshell *msh)
{
	msh->tokens = NULL;
	msh->info = malloc(sizeof(t_token_inf *));
	msh->envlist = NULL;
	msh->env = NULL;
	msh->prompt = NULL;
	msh->path = NULL;
	msh->lineread = NULL;
}

void	shell_free(t_mshell *msh)
{
	free (msh->env);
	if (msh->tokens)
		token_clear(&msh->tokens);
	env_list_clear(&msh->envlist);
	env_string_clear(msh->env);
	if (msh->lineread)
		free(msh->lineread);
	free (msh->info);
}

int	main(int argc, char *argv[], char *env[])
{
	t_mshell	msh;

	(void)argv;
	(void)argc;
	shell_init(&msh);
	env_init(&msh.envlist, env);
	env_set_string(&msh.envlist, &msh.env);
	msh.prompt = env_get_value(&msh.envlist, "PS1");
	msh.path = env_get_value(&msh.envlist, "PATH");
	input_cycle(&msh);
	shell_free(&msh);	// env is freed in shell_free:env_clear
	return (0);
}
