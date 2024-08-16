/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 18:52:11 by akretov          ###   ########.fr       */
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
		if (token->comtype == C_EXIT)
			com_exit(msh, token);
		else if (token->comtype == C_ECHO)
			com_echo(msh, token);
		else if (token->comtype == C_ENV)
			com_env(&msh->envlist, ENVVAR);
		else if (token->comtype == C_UNSET)
			com_unset(msh);
		else if (token->comtype == C_EXPORT)
			com_export(msh, token, ENVVAR);
		else if (token->comtype == C_ASSIGN)
			com_export(msh, token, SHLVAR);
		else if (token->comtype == C_CD)
			com_cd(msh, token);
		else
			return (1);
	}
	return (0);
}

int	parse_error_print(t_tokenlist *token)
{
	printf("msh: syntax error near token ");
	printf("%d `%s\'\n", token->index + 1, token->expand);
	return (1);
}

int	parse_error_check(t_mshell *msh, t_tokenlist **tokens)
{
	t_tokenlist	*token;

	token = *tokens;
	if (token->mtctype == PIPE)
	{
		msh->exitcode = EX_SYNTAX_ERROR;
		return (parse_error_print(token));
	}
	while (token && token->next)
	{
		if (token->mtctype >= PIPE && token->next->mtctype >= PIPE)
		{
			msh->exitcode = EX_SYNTAX_ERROR;
			return (parse_error_print(token));
		}
		else
			token = token->next;
	}
	if (token->mtctype >= PIPE)
	{
		msh->exitcode = EX_SYNTAX_ERROR;
		return (parse_error_print(token));
	}
	else
		return (0);
}

void	input_cycle(t_mshell *msh)
{
	while (msh->running)
	{
		env_update_exitcode(msh, &msh->envlist);
		msh->lineread = readline(*msh->prompt);
		if (msh->lineread == NULL)
		{
		free(msh->lineread);
		//free everything in tokens?
		printf("Exiting shell...\n");
		break;
		}
		add_history(msh->lineread);

		if (tokenize(msh))
		{
			tokens_get_info(msh);
			if (msh->tokens && !parse_error_check(msh, &msh->tokens))
			{
				init_pipex(msh);
				ft_exec_cmd(msh);
				free_pipex(msh->pipex);
			}
		}
		input_cleanup(msh);
	}
}
