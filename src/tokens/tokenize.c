/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 17:17:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		token_parse(t_mshell *msh, int end)
{
	char	*input;
	char	*token;
	int		start;
	int		i;

	i = 0;
	input = msh->lineread;
	while (input[end] && is_whitespace(input[end]))
		end++;
	start = end;
	while (input[end] && !is_whitespace(input[end]))
		end++;
	if ((end - start) > 0)
	{
		token = malloc(sizeof(char) * (end - start + 1));
		while (start < end)
			token[i++] = input[start++];
		token[i] = '\0';
		token_new(msh, token, end - i);
		free(token);
	}
	return (i + 1);
}

void	tokenize(t_mshell *msh)
{
	int i;

	i = 0;
	if (msh->lineread)
	{
		while (msh->lineread[i])
			i += token_parse(msh, i);
	}
	else
		token_clear(&msh->tokens);
}
