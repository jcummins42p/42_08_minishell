/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:58:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/31 14:14:56 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_parse_generic(t_mshell *msh, int *end)
{
	char	*token;
	int		len;
	int		start;
	int		i;

	i = 0;
	while (is_whitespace(msh->lineread[*end]))
		(*end)++;
	start = *end;
	while (msh->lineread[*end] && !is_metachar(&msh->lineread[*end]) \
		&& !is_whitespace(msh->lineread[*end]))
		(*end)++;
	len = *end - start;
	if (len > 0)
	{
		token = malloc(sizeof(char) * len + 1);
		while (i < len)
			token[i++] = msh->lineread[start++];
		token[len] = '\0';
		token_new(msh, token, *end - len);
		free (token);
		return (1);
	}
	else
		return (0);
}

int	token_parse_metachar(t_mshell *msh, int *i)
{
	t_mtctype	metachar;

	metachar = is_metachar(&msh->lineread[*i]);
	if (metachar == DOLLAR)
		*i += token_new(msh, "$", *i);
	else if (metachar == SQUOTE)
		*i += token_new(msh, "'", *i);
	else if (metachar == DQUOTE)
		*i += token_new(msh, "\"", *i);
	else if (metachar == PIPE)
		*i += token_new(msh, "|", *i);
	else if (metachar == RDAPP)
		*i += token_new(msh, ">>", *i);
	else if (metachar == DELIMIT)
		*i += token_new(msh, "<<", *i);
	else if (metachar == RDOUT)
		*i += token_new(msh, ">", *i);
	else if (metachar == RDIN)
		*i += token_new(msh, "<", *i);
	return (metachar);
}

int	token_parse_builtin(t_mshell *msh, int *i)
{
	t_comtype	command;

	command = is_builtin(&msh->lineread[*i]);
	if (command == ECHO)
		*i += token_new(msh, "echo", *i);
	else if (command == CD)
		*i += token_new(msh, "cd", *i);
	else if (command == PWD)
		*i += token_new(msh, "pwd", *i);
	else if (command == EXPORT)
		*i += token_new(msh, "export", *i);
	else if (command == UNSET)
		*i += token_new(msh, "unset", *i);
	else if (command == ENV)
		*i += token_new(msh, "env", *i);
	else if (command == EXIT)
		*i += token_new(msh, "exit", *i);
	return (command);
}


