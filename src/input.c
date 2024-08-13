/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/13 15:07:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_cleanup(t_mshell *msh)
{
	token_clear(&msh->tokens);
	free(msh->lineread);
	msh->lineread = NULL;
}

int	exec_builtin(t_mshell *msh, t_tokenlist *token)
{
	if (!token)
		return (1);
	else
	{
		if (token->comtype == EXIT)
			exec_exit(msh, token);
		else if (token->comtype == ECHO)
			echo_tokens(msh, token);
		else if (token->comtype == ENV)
			env_print(&msh->envlist, ENVVAR);
		else if (token->comtype == UNSET)
			unset(msh);
		else if (token->comtype == EXPORT)
			export_var(msh, token, ENVVAR);
		else if (token->comtype == ASSIGN)
			export_var(msh, token, SHLVAR);
		else if (token->comtype == CD)
			change_dir(msh, token);	//need to check if token->next->token exists
		else
			return (1);
	}
	return (0);
}

int	parse_error_print(t_tokenlist *token)
{
	printf("msh: syntax error near token");
	printf("%d `%s\'\n", token->index + 1, token->expand);
	return (1);
}

int	parse_error_check(t_tokenlist **tokens)
{
	t_tokenlist	*token;

	token = *tokens;
	if (token->mtctype == PIPE)
		return (parse_error_print(token));
	while (token && token->next)
	{
		if (token->mtctype == PIPE && token->next->mtctype == PIPE)
			return (parse_error_print(token));
		else
			token = token->next;
	}
	if (token->mtctype >= PIPE)
		return (parse_error_print(token));
	else
		return (0);
}

void	input_cycle(t_mshell *msh)
{
	while (msh->running)
	{
		env_update_exitcode(msh, &msh->envlist);
		msh->lineread = readline(*msh->prompt);
		add_history(msh->lineread);
		if (tokenize(msh))
		{
			tokens_get_info(msh);
			/*tokens_print_list(&msh->tokens);*/
			if (msh->tokens && !parse_error_check(&msh->tokens))
			{
				pipex_init(msh);
				ft_exec_init(msh);
			}
		}
		input_cleanup(msh);
	}
}
