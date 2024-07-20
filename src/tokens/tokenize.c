/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/20 19:21:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_is_metachar(t_tokenlist **tokens, char *str, int *i)
{
	bool	ismeta;

	ismeta = true;
	if (!strncmp(&str[*i], "$", 1))
		*i += token_new(tokens, "$", *i);
	else if (!strncmp(&str[*i], "'", 1))
		*i += token_new(tokens, "'", *i);
	else if (!strncmp(&str[*i], "\"", 1))
		*i += token_new(tokens, "\"", *i);
	else if (!strncmp(&str[*i], "|", 1))
		*i += token_new(tokens, "|", *i);
	else if (!strncmp(&str[*i], ">>", 2))
		*i += token_new(tokens, ">>", *i);
	else if (!strncmp(&str[*i], "<<", 2))
		*i += token_new(tokens, "<<", *i);
	else if (!strncmp(&str[*i], ">", 1))
		*i += token_new(tokens, ">", *i);
	else if (!strncmp(&str[*i], "<", 1))
		*i += token_new(tokens, "<", *i);
	else
		ismeta = false;
	return (ismeta);
}

bool	token_is_command(t_tokenlist **tokens, char *str, int *i)
{
	bool	iscommand;

	iscommand = true;
	if (!strncmp(&str[*i], "echo", 4))
		*i += token_new(tokens, "echo", *i);
	else if (!strncmp(&str[*i], "cat", 3))
		*i += token_new(tokens, "cat", *i);
	else if (!strncmp(&str[*i], "ls", 2))
		*i += token_new(tokens, "ls", *i);
	else if (!strncmp(&str[*i], "grep", 4))
		*i += token_new(tokens, "grep", *i);
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
			!token_is_command(tokens, str, &i))
			i++;
	}
}
