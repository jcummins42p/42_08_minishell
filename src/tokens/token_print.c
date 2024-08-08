/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:28:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/08 18:05:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_print_metachar(t_tokenlist *token)
{
	if (token->mtctype == DOLLAR)
		printf(" $ (variable) ");
	else if (token->mtctype == SQUOTE)
		printf(" ' (single quote) ");
	else if (token->mtctype == DQUOTE)
		printf(" \" (double quote) ");
	else if (token->mtctype == ASS)
		printf(" = (assign) ");
	else if (token->mtctype == PIPE)
		printf(" | (pipe) ");
	else if (token->mtctype == RDAPP)
		printf(" >> (append output) ");
	else if (token->mtctype == DELIMIT)
		printf(" << (delimit input) ");
	else if (token->mtctype == RDOUT)
		printf(" > (overwrite output) ");
	else if (token->mtctype == RDIN)
		printf(" < (redirect in) ");
}

void	token_print_command(t_tokenlist *token)
{
	if (token->comtype == ECHO)
		printf(" echo ");
	else if (token->comtype == CD)
		printf(" cd ");
	else if (token->comtype == PWD)
		printf(" pwd ");
	else if (token->comtype == EXPORT)
		printf(" export ");
	else if (token->comtype == UNSET)
		printf(" unset ");
	else if (token->comtype == ENV)
		printf(" env ");
	else if (token->comtype == EXIT)
		printf(" exit ");
	else if (token->comtype == ASSIGN)
		printf(" assign ");
}

void	token_print_type(t_tokenlist *token)
{
	if (token->tokentype == COMMAND)
	{
		printf("\n\tis a command of type: ");
		token_print_command(token);
	}
	else if (token->tokentype == METACHAR)
	{
		printf("\n\tis a metacharacter of type: ");
		token_print_metachar(token);
	}
}

void	token_print_each(t_tokenlist *tok)
{
	printf("Token %d:\t%s at position %d ", tok->index, tok->token, tok->pos);
	if (tok->expand)
		printf(" expanding to %s", tok->expand);
}

void	tokens_print_list(t_tokenlist **tokens)
{
	t_tokenlist	*curr;

	if (tokens == NULL || *tokens == NULL)
		return ;
	curr = *tokens;
	while (curr)
	{
		token_print_each(curr);
		token_print_type(curr);
		curr = curr->next;
		printf("\n");
	}
}
