/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/31 12:49:56 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_read(t_mshell *msh)
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

void	input_cleanup(t_mshell *msh)
{
	token_clear(&msh->tokens);
	free(msh->lineread);
	msh->lineread = NULL;
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
		if (input_read(msh))
			break ;
		input_cleanup(msh);
	}
}

void	shell_init(t_mshell *msh)
{
	msh->tokens = NULL;
	msh->info = malloc(sizeof(t_token_inf));
	msh->envlist = NULL;
	msh->env = NULL;
	msh->prompt = NULL;
	msh->path = NULL;
	msh->lineread = NULL;
	msh->running = true;
}

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
