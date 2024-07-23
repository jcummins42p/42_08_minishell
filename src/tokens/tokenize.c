/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 18:16:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_is_metachar(t_envlist **envlist, t_tokenlist **tokens, char *str, int *i)
{
	bool	ismeta;

	ismeta = true;
	if (!ft_strncmp(&str[*i], "$", 1))
	{
		*i += token_new(envlist, tokens, "$", str, *i);
	}
	else if (!ft_strncmp(&str[*i], "'", 1))
		*i += token_new(envlist, tokens, "'", str, *i);
	else if (!ft_strncmp(&str[*i], "\"", 1))
		*i += token_new(envlist, tokens, "\"", str, *i);
	else if (!ft_strncmp(&str[*i], "|", 1))
		*i += token_new(envlist, tokens, "|", str, *i);
	else if (!ft_strncmp(&str[*i], ">>", 2))
		*i += token_new(envlist, tokens, ">>", str, *i);
	else if (!ft_strncmp(&str[*i], "<<", 2))
		*i += token_new(envlist, tokens, "<<", str, *i);
	else if (!ft_strncmp(&str[*i], ">", 1))
		*i += token_new(envlist, tokens, ">", str, *i);
	else if (!ft_strncmp(&str[*i], "<", 1))
		*i += token_new(envlist, tokens, "<", str, *i);
	else
		ismeta = false;
	return (ismeta);
}

bool	token_is_builtin(t_mshell *msh, int *i)
{
	t_tokenlist	**tokens;
	t_envlist	**envlist;
	char		**str;
	bool		iscommand;

	tokens = &msh->tokens;
	envlist = &msh->envlist;
	str = &msh->lineread;

	iscommand = true;
	if (!ft_strncmp(&(*str)[*i], "echo", 4))
		*i += token_new(envlist, tokens, "echo", *str, *i);
	else if (!ft_strncmp(&(*str)[*i], "cd", 2))
		*i += token_new(envlist, tokens, "cd", *str, *i);
	else if (!ft_strncmp(&(*str)[*i], "pwd", 3))
		*i += token_new(envlist, tokens, "pwd", *str, *i);
	else if (!ft_strncmp(&(*str)[*i], "export", 6))
		*i += token_new(envlist, tokens, "export", *str, *i);
	else if (!ft_strncmp(&(*str)[*i], "unset", 5))
		*i += token_new(envlist, tokens, "unset", *str, *i);
	else if (!ft_strncmp(&(*str)[*i], "env", 3))
		*i += token_new(envlist, tokens, "env", *str, *i);
	else if (!ft_strncmp(&(*str)[*i], "exit", 4))
		*i += token_new(envlist, tokens, "exit", *str, *i);
	else
		iscommand = false;
	return (iscommand);
}

void	tokenize(t_mshell *msh)
{
	t_tokenlist	**tokens;
	char		**lineread;
	int	i;

	tokens = &msh->tokens;
	lineread = &msh->lineread;
	i = 0;
	while (*lineread && (*lineread)[i])
	{
		if (!token_is_metachar(&msh->envlist, tokens, *lineread, &i) && \
			!token_is_builtin(msh, &i))
			i++;
	}
}
