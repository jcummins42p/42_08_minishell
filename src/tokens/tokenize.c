/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 20:35:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_is_metachar(t_mshell *msh, int *i)
{
	bool		ismeta;

	ismeta = true;
	if (!ft_strncmp(&msh->lineread[*i], "$", 1))
		*i += token_new(msh, "$", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], "'", 1))
		*i += token_new(msh, "'", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], "\"", 1))
		*i += token_new(msh, "\"", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], "|", 1))
		*i += token_new(msh, "|", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], ">>", 2))
		*i += token_new(msh, ">>", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], "<<", 2))
		*i += token_new(msh, "<<", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], ">", 1))
		*i += token_new(msh, ">", *i, METACHAR);
	else if (!ft_strncmp(&msh->lineread[*i], "<", 1))
		*i += token_new(msh, "<", *i, METACHAR);
	else
		ismeta = false;
	return (ismeta);
}

bool	token_is_builtin(t_mshell *msh, int *i)
{
	bool		iscommand;

	iscommand = true;
	if (!ft_strncmp(&msh->lineread[*i], "echo", 4))
		*i += token_new(msh, "echo", *i, COMMAND);
	else if (!ft_strncmp(&msh->lineread[*i], "cd", 2))
		*i += token_new(msh, "cd", *i, COMMAND);
	else if (!ft_strncmp(&msh->lineread[*i], "pwd", 3))
		*i += token_new(msh, "pwd", *i, COMMAND);
	else if (!ft_strncmp(&msh->lineread[*i], "export", 6))
		*i += token_new(msh, "export", *i, COMMAND);
	else if (!ft_strncmp(&msh->lineread[*i], "unset", 5))
		*i += token_new(msh, "unset", *i, COMMAND);
	else if (!ft_strncmp(&msh->lineread[*i], "env", 3))
		*i += token_new(msh, "env", *i, COMMAND);
	else if (!ft_strncmp(&msh->lineread[*i], "exit", 4))
		*i += token_new(msh, "exit", *i, COMMAND);
	else
		iscommand = false;
	return (iscommand);
}

void	tokenize(t_mshell *msh)
{
	int	i;

	i = 0;
	if (msh->lineread)
	{
		while (msh->lineread[i])
		{
			while (is_whitespace(msh->lineread[i]))
				i++;
			if (!token_is_metachar(msh, &i) && \
				!token_is_builtin(msh, &i))
				i++;
		}
	}
	else
		token_clear(&msh->tokens);
}
