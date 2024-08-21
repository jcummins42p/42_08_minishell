/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/21 16:16:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_cleanup(t_mshell *msh)
{
	token_clear(&msh->tokens);
	free(msh->lineread);
	msh->lineread = NULL;
}

int	parse_error_print(t_mshell *msh, t_tokenlist *token)
{
	msh->valid_input = INVALID_IN;
	printf("msh: syntax error near token ");
	printf("%d `%s\'\n", token->index + 1, token->expand);
	return (INVALID_IN);
}

int	parse_error_check(t_mshell *msh, t_tokenlist **tokens)
{
	t_tokenlist	*token;

	token = *tokens;
	if (token->mtctype == PIPE)
	{
		msh->exitcode = EX_SYNTAX_ERROR;
		return (parse_error_print(msh, token));
	}
	while (token && token->next)
	{
		if (token->mtctype >= PIPE && (token->next->mtctype == PIPE))
		{
			msh->exitcode = EX_SYNTAX_ERROR;
			return (parse_error_print(msh, token));
		}
		else
			token = token->next;
	}
	if (token->mtctype >= PIPE)
		return (NO_PIPE);
	else
		return (0);
}

int	input_extend(t_mshell *msh)
{
	char	*swap;

	if (!msh->tokens)
		return (1);
	while (msh->valid_input || parse_error_check(msh, &msh->tokens) == NO_PIPE)
	{
		token_clear(&msh->tokens);
		swap = ft_strdup(msh->lineread);
		free (msh->lineread);
		msh->buff = readline("> ");
		if (msh->buff == NULL)
		{
			free(swap);
			free(msh->buff);
			return (1);
		}
		else
		{
			msh->lineread = ft_strjoin(swap, msh->buff);
			tokenize(msh, msh->lineread);
			free(msh->buff);
			free(swap);
		}
	}
	return (0);
}

void	input_cycle(t_mshell *msh)
{
	while (msh->running)
	{
		sig_init(msh);
		env_update_exitcode(msh, &msh->envlist);
		msh->lineread = readline(*msh->prompt);
		if (msh->lineread == NULL)
		{
			free(msh->lineread);
			break ;
		}
		tokenize(msh, msh->lineread);
		if (msh->lineread && msh->lineread[0] && !input_extend(msh))
			add_history(msh->lineread);
		if (msh->valid_input == VALID_IN)
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
