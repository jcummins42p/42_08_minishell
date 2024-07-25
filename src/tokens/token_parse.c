/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:58:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/24 17:58:35 by jcummins         ###   ########.fr       */
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
	start = *end;
	while (msh->lineread[*end] && !is_metachar(&msh->lineread[*end]) \
			&& !is_builtin(&msh->lineread[*end]))
		(*end)++;
	len = *end - start;
	if (len > 0)
	{
		token = malloc(sizeof(char) * len + 1);
		while (i < len)
		{
			token[i++] = msh->lineread[start++];
		}
		token[len] = '\0';
		token_new(msh, token, *end - len, GENERIC);
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
		*i += token_new(msh, "$", *i, METACHAR);
	else if (metachar == SQUOTE)
		*i += token_new(msh, "'", *i, METACHAR);
	else if (metachar == DQUOTE)
		*i += token_new(msh, "\"", *i, METACHAR);
	else if (metachar == PIPE)
		*i += token_new(msh, "|", *i, METACHAR);
	else if (metachar == RDAPP)
		*i += token_new(msh, ">>", *i, METACHAR);
	else if (metachar == DELIMIT)
		*i += token_new(msh, "<<", *i, METACHAR);
	else if (metachar == RDOUT)
		*i += token_new(msh, ">", *i, METACHAR);
	else if (metachar == RDIN)
		*i += token_new(msh, "<", *i, METACHAR);
	return (metachar);
}

int	token_parse_builtin(t_mshell *msh, int *i)
{
	t_comtype	command;

	command = is_builtin(&msh->lineread[*i]);
	if (command == ECHO)
		*i += token_new(msh, "echo", *i, COMMAND);
	else if (command == CD)
		*i += token_new(msh, "cd", *i, COMMAND);
	else if (command == PWD)
		*i += token_new(msh, "pwd", *i, COMMAND);
	else if (command == EXPORT)
		*i += token_new(msh, "export", *i, COMMAND);
	else if (command == UNSET)
		*i += token_new(msh, "unset", *i, COMMAND);
	else if (command == ENV)
		*i += token_new(msh, "env", *i, COMMAND);
	else if (command == EXIT)
		*i += token_new(msh, "exit", *i, COMMAND);
	return (command);
}
