/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/22 18:01:11 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_is_metachar(t_tokenlist **tokens, char *str, int *i)
{
	bool	ismeta;

	ismeta = true;
	if (!ft_strncmp(&str[*i], "$", 1))
	{
		*i += token_new(tokens, "$", str, *i);
	}
	else if (!ft_strncmp(&str[*i], "'", 1))
		*i += token_new(tokens, "'", str, *i);
	else if (!ft_strncmp(&str[*i], "\"", 1))
		*i += token_new(tokens, "\"", str, *i);
	else if (!ft_strncmp(&str[*i], "|", 1))
		*i += token_new(tokens, "|", str, *i);
	else if (!ft_strncmp(&str[*i], ">>", 2))
		*i += token_new(tokens, ">>", str, *i);
	else if (!ft_strncmp(&str[*i], "<<", 2))
		*i += token_new(tokens, "<<", str, *i);
	else if (!ft_strncmp(&str[*i], ">", 1))
		*i += token_new(tokens, ">", str, *i);
	else if (!ft_strncmp(&str[*i], "<", 1))
		*i += token_new(tokens, "<", str, *i);
	else
		ismeta = false;
	return (ismeta);
}

bool	token_is_builtin(t_tokenlist **tokens, char *str, int *i)
{
	bool	iscommand;

	iscommand = true;
	if (!ft_strncmp(&str[*i], "echo", 4))
		*i += token_new(tokens, "echo", str, *i);
	else if (!ft_strncmp(&str[*i], "cd", 2))
		*i += token_new(tokens, "cd", str, *i);
	else if (!ft_strncmp(&str[*i], "pwd", 3))
		*i += token_new(tokens, "pwd", str, *i);
	else if (!ft_strncmp(&str[*i], "export", 6))
		*i += token_new(tokens, "export", str, *i);
	else if (!ft_strncmp(&str[*i], "unset", 5))
		*i += token_new(tokens, "unset", str, *i);
	else if (!ft_strncmp(&str[*i], "env", 3))
		*i += token_new(tokens, "env", str, *i);
	else if (!ft_strncmp(&str[*i], "exit", 4))
		*i += token_new(tokens, "exit", str, *i);
	else
		iscommand = false;
	return (iscommand);
}

void	tokenize(t_tokenlist **tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!token_is_metachar(tokens, str, &i) && \
			!token_is_builtin(tokens, str, &i))
			i++;
	}
}
